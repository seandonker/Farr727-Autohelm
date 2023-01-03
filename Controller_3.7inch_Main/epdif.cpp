#include "epdif.h"
#include <spi.h>

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
    digitalWrite(pin, value);
}

int EpdIf::DigitalRead(int pin) {
    return digitalRead(pin);
}

//void EpdIf::DelayMs(unsigned int delaytime) {
//    delay(delaytime);
//}
void EpdIf::delayWithIMU(int delayMili){ //min delay time is 20 ms, error up to +20 ms
  unsigned long funcTimer = millis();
  while( (funcTimer + delayMili) > millis() ){
    IMU_Routine();
  }
}

void EpdIf::SpiTransfer(unsigned char data) {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
}

int EpdIf::IfInit(void) {
    pinMode(CS_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT); 
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    
    return 0;
}
