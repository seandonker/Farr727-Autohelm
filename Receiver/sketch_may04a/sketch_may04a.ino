#include "SPI.h"
#include "NRFLite.h"
#include <AccelStepper.h>
#define DIR_PIN 3
#define STEP_PIN 4
#define EN_PIN 1

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t DESTINATION_RADIO_ID = 1; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 23;
const static uint8_t PIN_RADIO_CSN = 2;
//const static uint8_t PIN_LIMIT_SWITCH = 20;
const int analogPin = A8;
//volatile int limitSwitch = 0;
int prevError = 0;
int PID_Output = 0;
int P, I, D = 0;
int stepperSpeed = 0;
int extensionLength = 288000; //360 mm, 2mm pitch, 360/2 * 1600

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
long timer;
long timer2;
int timerPID;

struct RadioPacket_Controller{ //sending 10 bytes
  short errorHeading; // 2 bytes, 0-65,535
  unsigned short Proportional;
  unsigned short Integral;
  unsigned short Derivative;
  //unsigned short Heel;     //tilt of boat
};

struct RadioPacket_Receiver{ //sending 2 bytes
  unsigned char BatteryVoltage; 
};

NRFLite radio;
RadioPacket_Receiver radioData_Receiver;
RadioPacket_Controller radioData_Controller;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN, true); 

void setup()
{  
  Serial.begin(115200);
  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100)){
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
  radioData_Controller.errorHeading = 0;
  
  pinMode(1, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(PIN_LIMIT_SWITCH), interrupt_LimitSwitch, RISING);
  digitalWrite(1,LOW);
  
  stepper.setMaxSpeed(5000); //8000 maxish
  stepper.setAcceleration(8000); //5000
  stepper.setCurrentPosition(0);
  //homeStepper();
  timer = millis();
  timer2 = millis();
  //timer3 = millis(); //saftey stop
  //Serial.println(stepper.targetPosition());
}

void loop()
{
    if(stepperSpeed == 0 && ((millis() - timer) > 10000)){      //every 10 seconds, send 
      sensorValue = analogRead(analogPin);
      outputValue = map(sensorValue, 0, 1023, 0, 262); //increase of reading low
      radioData_Receiver.BatteryVoltage = outputValue - 69; //scaleFactor, so less than 255
      radio.send(DESTINATION_RADIO_ID, &radioData_Receiver, sizeof(radioData_Receiver));
      Serial.println("SENDING BLUETOOTH");
      Serial.println(radioData_Receiver.BatteryVoltage);
      timer = millis();
    }
    stepper.runSpeed();
    
    if (radio.hasData()) //uses while for some reason?
    {
        prevError = radioData_Controller.errorHeading;
        radio.readData(&radioData_Controller);
        timerPID = millis() - timer2;
        
//        P = radioData_Controller.Proportional * radioData_Controller.errorHeading;
//        I += radioData_Controller.Integral * (radioData_Controller.errorHeading * timerPID);
//        D = radioData_Controller.Derivative * (radioData_Controller.errorHeading - prevError)/timerPID;
//        PID_Output = P + I + D;
//        timer2 = millis();

        P = 1000 * radioData_Controller.errorHeading/5; //1-500 ish
        //I += 0 * (radioData_Controller.errorHeading * timerPID) / 2000; //1-500 ish
        I = 0;
        D = 0 * ((double)(radioData_Controller.errorHeading - prevError)* 1500)/(double)(timerPID); //1-500 ish
        PID_Output = P + I + D;
        timer2 = millis();
        stepperSpeed = -PID_Output/10; //8000 maxish
        stepper.setSpeed(stepperSpeed);
        //if(radioData_Controller.errorHeading > 0)
        //  stepper.move(-800*10); //800 for 1 rot (1/4)
        //else
        //  stepper.move(800*10); //800 for 1 rot  (1/4)
        String msg = "ERROR :";
        msg += radioData_Controller.errorHeading;
        msg += ", P: ";
        msg += P;
        msg += " , I:";
        msg += I;
        msg += " , D:";
        msg += D;

        Serial.println(msg);
    }
}

//void interrupt_LimitSwitch(){
//  noInterrupts();
//  if(limitSwitch == 0)
//    limitSwitch = 1;
//  interrupts();
//}

void homeStepper(){
  while(1){
    stepper.runToNewPosition(-50000); //36 cm,move to hit limit switch
    stepper.runToNewPosition(+50000); //36 cm,move to hit limit switch
  }
  stepper.runToNewPosition(-extensionLength-3200); //36 cm,move to hit limit switch
  delay(1000);
  stepper.setCurrentPosition(-1600);  //home position is 0, don't want to repeatedly hit switch
  stepper.moveTo(0); //800 for 1 rot (1/4)
  stepper.runToPosition();
  delay(2000);
  stepper.moveTo(extensionLength/2);  //move out to half extension
  stepper.runToPosition();
}
