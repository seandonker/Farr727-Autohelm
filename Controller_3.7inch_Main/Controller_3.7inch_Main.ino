#include <Wire.h>
#include <LSM6.h>
#include <LIS3MDL.h>
#include <SPI.h>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "epd3in7.h"
#include "imagedata.h"
#include "epdpaint.h"
#include "NRFLite.h"
#include "RTClib.h"

void IMU_Routine(void);
void delayWithIMU(int delayMili);
//*********************************************************DISPLAY
#define COLORED     0
#define UNCOLORED   1
Epd epd;
UBYTE baseBlank_Image[16800];                  //280 x 480 / 8
UBYTE baseHome_Image[16800];
UBYTE holdHome_Image[16800];
UBYTE setHome_Image[16800];
UBYTE menuHome_Image[16800];
UBYTE PIDHome_Image[16800];
Paint baseHome(baseHome_Image, 280, 480);    //base screen without info (should never display this), width should be the multiple of 8 
Paint holdHome(holdHome_Image, 280, 480);    //after startup, not set heading yet
Paint setHome(setHome_Image, 280, 480);     //heading set, home screen
Paint baseBlank(baseBlank_Image, 280, 480);   //blank home
Paint menuHome(menuHome_Image, 280, 480);     //menu home
Paint PIDHome(PIDHome_Image, 280, 480);     //menu home
char headingString[6];

//*********************************************************RADIO
const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio to transmit to.
const static uint8_t PIN_RADIO_CE = 17;  //CHANGE TO 17 for pcb
const static uint8_t PIN_RADIO_CSN = 14;
const int analogPin = A7;

struct RadioPacket_Controller{ //sending 10 bytes, un
  //unsigned short 0 -> 65535, signed short -32768 -> 32767 (both 2 bytes, 16 bits)
  short errorHeading;
  unsigned short Proportional = 5;
  unsigned short Integral = 6;
  unsigned short Derivative = 7;
  short Heel;     //tilt of boat
};
struct RadioPacket_Receiver{ //sending 2 bytes
  unsigned char BatteryVoltage; 
};
//RadioPacket_Receiver.BatteryVoltage = 0;
NRFLite radio;
RadioPacket_Receiver radioData_Receiver;
RadioPacket_Controller radioData_Controller;

//*********************************************************IMU
LSM6 gyro_acc;
LIS3MDL mag;
int SENSOR_SIGN[9] = {1,1,1,-1,-1,-1,1,1,1}; //Correct directions x,y,z - gyro, accelerometer, magnetometer
#define GRAVITY 256  //this equivalent to 1G in the raw data coming from the accelerometer
#define ToRad(x) ((x)*0.01745329252)  // *pi/180
#define ToDeg(x) ((x)*57.2957795131)  // *180/pi
#define Gyro_Gain_X 0.07 //X axis Gyro gain
#define Gyro_Gain_Y 0.07 //Y axis Gyro gain
#define Gyro_Gain_Z 0.07 //Z axis Gyro gain
#define Gyro_Scaled_X(x) ((x)*ToRad(Gyro_Gain_X)) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Y(x) ((x)*ToRad(Gyro_Gain_Y)) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Z(x) ((x)*ToRad(Gyro_Gain_Z)) //Return the scaled ADC raw data of the gyro in radians for second

#define M_X_MIN -2988   //Calibrate sensor by running calibration and "painting inside of sphere"
#define M_Y_MIN 761
#define M_Z_MIN -9586
#define M_X_MAX 4465
#define M_Y_MAX 7950
#define M_Z_MAX -2324

#define Kp_ROLLPITCH 0.02
#define Ki_ROLLPITCH 0.00002
#define Kp_YAW 1.2
#define Ki_YAW 0.00002
#define STATUS_LED 13

float G_Dt=0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer=0;   //general purpuse timer
long timer_old;
long loop_start = 0;
long loop_end = 0;
long timer24=0; //Second timer used to print values
int AN[6]; //array that stores the gyro and accelerometer data
int AN_OFFSET[6]={0,0,0,0,0,0}; //Array that stores the Offset of the sensors

int gyro_x;
int gyro_y;
int gyro_z;
int accel_x;
int accel_y;
int accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
float c_magnetom_x;
float c_magnetom_y;
float c_magnetom_z;
float MAG_Heading;

float Accel_Vector[3]= {0,0,0}; //Store the acceleration in a vector
float Gyro_Vector[3]= {0,0,0};//Store the gyros turn rate in a vector
float Omega_Vector[3]= {0,0,0}; //Corrected Gyro_Vector data
float Omega_P[3]= {0,0,0};//Omega Proportional correction
float Omega_I[3]= {0,0,0};//Omega Integrator
float Omega[3]= {0,0,0};
// Euler angles
float roll;
float pitch;
float yaw;
float errorRollPitch[3]= {0,0,0};
float errorYaw[3]= {0,0,0};
unsigned int counter=0;
byte gyro_sat=0;
float DCM_Matrix[3][3]={{1,0,0},{0,1,0},{0,0,1}};
float Update_Matrix[3][3]={{0,1,2},{3,4,5},{6,7,8}}; //Gyros here
float Temporary_Matrix[3][3]={{0,0,0},{0,0,0},{0,0,0}};

//*********************************************************GENERAL
#define LEFTLEFT_BUT_PIN 5
#define LEFT_BUT_PIN 4
#define RIGHT_BUT_PIN 3
#define RIGHTRIGHT_BUT_PIN 2

volatile int buttonStates[4] = {0, 0, 0, 0}; //White, Red, Green, Yellow. Even is finished button excecution.
static unsigned long last_interrupt = 0;
unsigned long interrupt = 0;
int currentlyActive = 0;   //ZERO FALSE
int setHeading = 0;
short actualHeading=0;
int buttonStateSum;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
double averageOutput[5] = {0,0,0,0,0};
short controlActive = 0; //0 false, 1 true, unit starts by not moving

RTC_DS3231 rtc;

void setup() {
  IMU_Init(); //accel, gyro, and compass
  Peripheral_Init(); //e-paper, rtc, button interrupts, radio
  Epaper_base_designs();

  //epd.Init();
  timer=millis();
  counter=0;
  
  epd.Init();
  epd.DisplayFrame(holdHome.GetImage(), true);
  Serial.println("*****SETUP DONE*****\n\n");
  epd.Sleep();
}

void loop() {
  //IMU_Routine(); //This routine has radio send function as well at 50hz

  buttonStateSum = 0;
  for(int i = 0; i < 4; i++){ //creates sum of button states, (states change from interrupt)
    buttonStateSum += buttonStates[i];
  }
  if(buttonStateSum % 2 != 0) //runs if odd, (button press)
    handleButtonStates();  //ISR change button states, this function displays menu depending on states
  if (radio.hasData()){
    //epd.DisplayFrame(baseBlank.GetImage(), true);
  }
}
