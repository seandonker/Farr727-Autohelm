void Epaper_base_designs(){
  baseBlank.SetRotate(ROTATE_90);  //
  baseHome.SetRotate(ROTATE_90);
  holdHome.SetRotate(ROTATE_90);
  setHome.SetRotate(ROTATE_90);
  menuHome.SetRotate(ROTATE_90);
  PIDHome.SetRotate(ROTATE_90);
  DateTime now = rtc.now();
  /********************baseBlank SCREEN MAKING********************/ //includes heading, status, button boxes, voltage and time
  baseBlank.Clear(UNCOLORED);
  baseBlank.DrawStringAt(40,70, "HEADING", &Font63, COLORED);
  baseBlank.DrawFilledCircle(40+168+10, 80, 3, COLORED);
  baseBlank.DrawFilledCircle(40+168+10, 100, 3, COLORED);
  baseBlank.DrawStringAt(40,120,  "STATUS", &Font63, COLORED);
  baseBlank.DrawFilledCircle(40+168+10, 130, 3, COLORED);
  baseBlank.DrawFilledCircle(40+168+10, 150, 3, COLORED);
  
  baseBlank.DrawFilledRectangle(17+(0 * 115), 200, 117+(0 * 115), 270, COLORED);
  baseBlank.DrawFilledRectangle(17+(1 * 115), 200, 117+(1 * 115), 270, COLORED);
  baseBlank.DrawFilledRectangle(17+(2 * 115), 200, 117+(2 * 115), 270, COLORED);
  baseBlank.DrawFilledRectangle(17+(3 * 115), 200, 117+(3 * 115), 270, COLORED);
  /*TIME PRINTING*/
  delay(1000);
  char timeString[10];
  char minuteString[4];
  itoa( now.hour(), timeString, 10);
  itoa( now.minute(), minuteString, 10);
  strcat(timeString, ":");
  if(strlen(minuteString) == 1){
    strcat(timeString, "0");
  }
  strcat(timeString , minuteString);
  baseBlank.DrawStringAt(5,5, timeString, &Font36, COLORED);

  /*BATTEY PRINTING*/

  char controlBattVoltage[6];
  char controlBattVoltageMV[3];
  outputValue = map(analogRead(analogPin), 0, 1023, 0, 554); //increase of reading low
  itoa(outputValue/100, controlBattVoltage,10);
  strcat(controlBattVoltage,".");
  if(outputValue%100 < 10){
    strcat(controlBattVoltage,"0");
  }
  itoa(outputValue%100, controlBattVoltageMV,10);
  strcat(controlBattVoltage,controlBattVoltageMV);
  strcat(controlBattVoltage, "V");
  baseBlank.DrawStringAt(205,5, controlBattVoltage, &Font36, COLORED);

  char battVoltage[6];
  if (radio.hasData()){ //uses while for some reason?
    radio.readData(&radioData_Controller);
    Serial.println("Getting thruster voltage");
  }
  itoa(radioData_Receiver.BatteryVoltage + 69, battVoltage,10);
  baseBlank.DrawStringAt(370,5, battVoltage, &Font36, COLORED);
/********************baseHome SCREEN MAKING********************/ //baseBlank + up/down 15 and menu
  baseHome.Clear(UNCOLORED);
  std::copy_n(baseBlank_Image, 16800, baseHome_Image);//std::copy_n(src, n, dest);
  //baseHome.DrawStringAt(93,127, "15", &Font24, UNCOLORED);
  //baseHome.DrawStringAt(167,127, "15", &Font24, UNCOLORED);
  baseHome.DrawStringAt(375,222,"MENU", &Font36, UNCOLORED);
  //baseHome.DrawCircle(129, 129, 2, UNCOLORED);   //degree symbol
  //baseHome.DrawCircle(203, 129, 2, UNCOLORED);   //degree symbol
  baseHome.DrawHorizontalLine(270, 238, 55, UNCOLORED);//RIGHT ARROW
  baseHome.DrawHorizontalLine(270, 239, 55, UNCOLORED);
  baseHome.DrawHorizontalLine(270, 240, 55, UNCOLORED);
  baseHome.DrawLine(325, 240, 295, 215, UNCOLORED);
  baseHome.DrawLine(326, 240, 294, 216, UNCOLORED);
  baseHome.DrawLine(327, 240, 293, 217, UNCOLORED);
  baseHome.DrawLine(325, 238,  295, 255,UNCOLORED);
  baseHome.DrawLine(326, 238,  294, 256,UNCOLORED);
  baseHome.DrawLine(327, 238,  293, 257,UNCOLORED);
  
  baseHome.DrawHorizontalLine(150, 238, 55, UNCOLORED);//LEFT ARROW
  baseHome.DrawHorizontalLine(150, 239, 55, UNCOLORED);
  baseHome.DrawHorizontalLine(150, 240, 55, UNCOLORED);
  baseHome.DrawLine(150, 240, 180, 215, UNCOLORED);
  baseHome.DrawLine(151, 240, 181, 216, UNCOLORED);
  baseHome.DrawLine(152, 240, 182, 217, UNCOLORED);
  baseHome.DrawLine(150, 238,  180, 255,UNCOLORED);
  baseHome.DrawLine(151, 238,  181, 256,UNCOLORED);
  baseHome.DrawLine(152, 238,  182, 257,UNCOLORED);
  

/********************holdHome SCREEN MAKING********************/ //baseHome + hold, "---", and set button option
  holdHome.Clear(UNCOLORED);
  std::copy_n(baseHome_Image, 16800, holdHome_Image);//std::copy_n(src, n, dest);
  holdHome.DrawStringAt(240,60, "---", &Font63, COLORED);
  holdHome.DrawStringAt(240,115,  "HOLD", &Font63, COLORED);
  holdHome.DrawStringAt(28,222, "SET", &Font36, UNCOLORED);
  //holdHome.DrawCircle(224, 23, 2, COLORED);   //degree symbol
/********************setHome SCREEN MAKING********************/ //baseHome + set, "362", and hold button option
  setHome.Clear(UNCOLORED);
  std::copy_n(baseHome_Image, 16800, setHome_Image);//std::copy_n(src, n, dest);
  
  setHome.DrawStringAt(240,115,  "SET", &Font63, COLORED);
  setHome.DrawStringAt(28,222, "HOLD", &Font36, UNCOLORED);
  //holdHome.DrawCircle(224, 23, 2, COLORED);   //degree symbol
  char headingString[5];
  itoa(ToHeading(), headingString ,10);
  setHome.DrawStringAt(240,60, headingString, &Font63, COLORED);
/********************menuHome SCREEN MAKING********************/
  menuHome.Clear(UNCOLORED);
  std::copy_n(baseBlank_Image, 16800, menuHome_Image);//std::copy_n(src, n, dest);
  menuHome.DrawStringAt(28,222, "PID", &Font36, UNCOLORED);
  menuHome.DrawStringAt(160,222, "IDK", &Font36, UNCOLORED);
  menuHome.DrawStringAt(270,222, "IDK", &Font36, UNCOLORED);
  menuHome.DrawStringAt(370,222, "BACK", &Font36, UNCOLORED);
/********************PIDHome SCREEN MAKING********************/
  char proportionalStr[7];
  char integralStr[7];
  char derivativeStr[7];
  PIDHome.Clear(UNCOLORED);
  std::copy_n(baseBlank_Image, 16800, PIDHome_Image);//std::copy_n(src, n, dest);
  PIDHome.DrawFilledRectangle(0, 40, 450, 180, UNCOLORED); //cover up heading/status
  
  PIDHome.DrawStringAt(80,60, "Proportional:", &Font36, COLORED);
  PIDHome.DrawStringAt(80,100, "Integral:", &Font36, COLORED);
  PIDHome.DrawStringAt(80,140, "Derivative:", &Font36, COLORED);
  itoa(radioData_Controller.Proportional, proportionalStr ,10);
  itoa(radioData_Controller.Integral, integralStr ,10);
  itoa(radioData_Controller.Derivative, derivativeStr ,10);
  PIDHome.DrawStringAt(320,60, proportionalStr, &Font36, COLORED);
  PIDHome.DrawStringAt(320,100, integralStr, &Font36, COLORED);
  PIDHome.DrawStringAt(320,140, derivativeStr, &Font36, COLORED);

  PIDHome.DrawStringAt(35,222, "P", &Font63, UNCOLORED);
  PIDHome.DrawStringAt(170,222, "I", &Font63, UNCOLORED);
  PIDHome.DrawStringAt(280,222, "D", &Font63, UNCOLORED);
  PIDHome.DrawStringAt(370,222, "BACK", &Font36, UNCOLORED);
}
