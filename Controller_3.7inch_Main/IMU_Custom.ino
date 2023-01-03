void printdata(void){      
      Serial.print("IMU heading:");
      Serial.print(ToDeg(yaw));
//      Serial.print("  Compass Heading:");
//      Serial.print(ToDeg(MAG_Heading));
//      Serial.print("  IMU Roll:");
//      Serial.print(ToDeg(roll));
      Serial.println();
}

int ToHeading(){
  actualHeading = ToDeg(yaw); 
  if(actualHeading < 0)
    actualHeading = actualHeading + 360;
  return actualHeading;
}

double ToDoubleHeading(){
  double doubleHeading;
  doubleHeading = ToDeg(yaw); 
  if(doubleHeading < 0)
    doubleHeading = doubleHeading + 360;  
  return doubleHeading;
}

int computeError(){  //scaled by x100!
  int error;
  actualHeading = ToDeg(yaw) * 100;
  //Serial.println(actualHeading/10);
  error = (setHeading  * 100) - actualHeading;
  if(abs(error) >= 18000){
    if(setHeading > actualHeading){
      return error - 36000;
    }
    return error + 36000;
  }
  return error;  
}

void updateHeading(int headingChange){
  if( (setHeading + headingChange) > 360){
    setHeading = setHeading + headingChange - 360; 
  }
  else if( (setHeading + headingChange) < 0){
    setHeading = setHeading + headingChange + 360;
  }
  else{
    setHeading += headingChange;
  }
}

void delayWithIMU(int delayMili){ //min delay time is 20 ms, error up to +20 ms
  unsigned long funcTimer = millis();
  while( (funcTimer + delayMili) > millis() ){
    IMU_Routine();
  }
}
