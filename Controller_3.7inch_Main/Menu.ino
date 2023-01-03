void handleButtonStates(){  //-1 if don't care about button state
  //A lot of optimizations can be made her but won't get back a lot of execution time,
  //more if statments for if in a menu or not

  
  if(wantedButtonStates(1,0,0,0)){//***************************************SET/HOLD HEADING
    buttonStates[0] = 0;
    if(controlActive != 0){ //if active..
      controlActive = 0;
      Serial.println("*********************HOLDING");//What screen?
      Serial.println("SET DOWN15 UP15 MENU");//Button states
    }
    else{
      controlActive = 1;
      Serial.println("*********************HEADING SET");//What screen? 
      Serial.println("HOLD DOWN15 UP15 MENU");//Button states
    }
    
    Serial.println("");
  }
  else if(wantedButtonStates(0,1,0,0)){//**********************************DOWN 15
    Serial.println("*********************DOWN 15");//What screen?
    if(controlActive != 0){ //if active..
      Serial.println("HOLD DOWN15 UP15 MENU");//Button states
    }
    else{
      Serial.println("SET DOWN15 UP15 MENU");//Button states
    }
    buttonStates[1] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(0,0,1,0)){//**********************************UP 15
    Serial.println("*********************UP 15");//What screen?
    if(controlActive != 0){ //if active..
      Serial.println("HOLD DOWN15 UP15 MENU");//Button states
    }
    else{
      Serial.println("SET DOWN15 UP15 MENU");//Button states
    }
    buttonStates[2] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(0,0,0,1)){//**********************************MENU
    Serial.println("*********************MENU");//What screen?
    Serial.println("PID TILT SERIAL BACK");//Button states
    buttonStates[3] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(0,0,0,3)){//**********************************MENU BACK
    if(controlActive != 0){ //if active..
      Serial.println("*********************HEADING SET");//What screen? 
      Serial.println("HOLD DOWN15 UP15 MENU");//Button states

    }
    else{
      Serial.println("*********************HOLDING");//What screen?
      Serial.println("SET DOWN15 UP15 MENU");//Button states
    }
    buttonStates[3] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(1,0,0,2)){//**********************************PIDS
    Serial.println("*********************PID CONTROL");//What screen?
    Serial.println("P    I    D     BACK");//Button states
    buttonStates[0] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(2,0,0,3)){//**********************************PID BACK
    Serial.println("*********************MENU");//What screen?
    Serial.println("PID TILT SERIAL BACK");//Button states
    buttonStates[0] = 0;
    buttonStates[3] = 2;
    Serial.println("");
  }
  
  //***********************************************************************PROPORTIONAL
  
  else if(wantedButtonStates(3,0,0,2) || wantedButtonStates(7,0,0,2)){//***PROPORTIONAL MENU COURSE
    Serial.println("*********************PROPORTIONAL COURSE");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[0] = 4;
    Serial.println("");
  }
  else if(wantedButtonStates(5,0,0,2)){//**********************************PROPORTIONAL MENU FINE
    Serial.println("*********************PROPORTIONAL FINE");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[0] = 6;
    Serial.println("");
  }
  else if(wantedButtonStates(4,1,0,2)){//**********************************PROPORTIONAL MENU COURSE DOWN
    Serial.println("*********************PROPORTIONAL COURSE DOWN");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[1] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(4,0,1,2)){//**********************************PROPORTIONAL MENU COURSE UP
    Serial.println("*********************PROPORTIONAL COURSE UP");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[2] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(6,1,0,2)){//**********************************PROPORTIONAL MENU FINE DOWN
    Serial.println("*********************PROPORTIONAL FINE DOWN");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[1] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(6,0,1,2)){//**********************************PROPORTIONAL MENU FINE UP
    Serial.println("*********************PROPORTIONAL FINE UP");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[2] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(4,0,0,3) || wantedButtonStates(6,0,0,3)){//**********************************PROPORTIONAL BACK
    Serial.println("*********************PID CONTROL");//What screen?
    Serial.println("P    I    D     BACK");//Button states
    buttonStates[3] = 2;
    buttonStates[0] = 2;
    Serial.println("");
  }
  
  //***********************************************************************INTEGRAL
  
   else if(wantedButtonStates(2,1,0,2) || wantedButtonStates(5,2,0,2)){//***INTEGRAL MENU COURSE
    Serial.println("*********************INTEGRAL COURSE");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[1] = 2;
    buttonStates[0] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(3,2,0,2)){//**********************************INTEGRAL MENU FINE
    Serial.println("*********************INTEGRAL FINE");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[0] = 4;
    Serial.println("");
  }
  else if(wantedButtonStates(2,3,0,2)){//**********************************INTEGRAL MENU COURSE DOWN
    Serial.println("*********************INTEGRAL COURSE DOWN");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[1] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(2,2,1,2)){//**********************************INTEGRAL MENU COURSE UP
    Serial.println("*********************INTEGRAL COURSE UP");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[2] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(4,3,0,2)){//**********************************INTEGRAL MENU FINE DOWN
    Serial.println("*********************INTEGRAL FINE DOWN");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[1] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(4,2,1,2)){//**********************************INTEGRAL MENU FINE UP
    Serial.println("*********************INTEGRAL FINE UP");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[2] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(2,2,0,3) || wantedButtonStates(4,2,0,3)){//**********************************INTEGRAL BACK
    Serial.println("*********************PID CONTROL");//What screen?
    Serial.println("P    I    D     BACK");//Button states
    buttonStates[0] = 2;
    buttonStates[1] = 0;
    buttonStates[3] = 2;
    Serial.println("");
  }
  
  //***********************************************************************DERRIVATIVE

  else if(wantedButtonStates(2,0,1,2) || wantedButtonStates(5,0,2,2)){//***DERRIVATIVE MENU COURSE
    Serial.println("*********************DERRIVATIVE COURSE");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[2] = 2;
    buttonStates[0] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(3,0,2,2)){//**********************************DERRIVATIVE MENU FINE
    Serial.println("*********************DERRIVATIVE FINE");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[0] = 4;
    Serial.println("");
  }
  else if(wantedButtonStates(2,1,2,2)){//**********************************DERRIVATIVE MENU COURSE DOWN
    Serial.println("*********************DERRIVATIVE COURSE DOWN");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[1] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(2,0,3,2)){//**********************************DERRIVATIVE MENU COURSE UP
    Serial.println("*********************DERRIVATIVE COURSE UP");//What screen?
    Serial.println("FINE DOWN UP BACK");//Button states
    buttonStates[2] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(4,1,2,2)){//**********************************DERRIVATIVE MENU FINE DOWN
    Serial.println("*********************DERRIVATIVE FINE DOWN");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[1] = 0;
    Serial.println("");
  }
  else if(wantedButtonStates(4,0,3,2)){//**********************************DERRIVATIVE MENU FINE UP
    Serial.println("*********************DERRIVATIVE FINE UP");//What screen?
    Serial.println("COURSE DOWN UP BACK");//Button states
    buttonStates[2] = 2;
    Serial.println("");
  }
  else if(wantedButtonStates(2,0,2,3) || wantedButtonStates(4,0,2,3)){//**********************************DERRIVATIVE BACK
    Serial.println("*********************PID CONTROL");//What screen?
    Serial.println("P    I    D     BACK");//Button states
    buttonStates[0] = 2;
    buttonStates[2] = 0;
    buttonStates[3] = 2;
    Serial.println("");
  }
}
//void handleButtonStates(){  //-1 if don't care about button state
//  
//  if(wantedButtonStates(1,0,0,0)){ //SET HEADING
//    epd.Init(); //regular refreshes, 0.82 seconds
//    //setHome.Clear(UNCOLORED);
//    //std::copy_n(baseHome_Image, 5800, setHome_Image);
//    //setHome.DrawStringAt(162,50,  "ACTIVE", &Font24, COLORED);
//    //setHome.DrawStringAt(5,115, "HOLD", &Font24, UNCOLORED);
//    ToHeading();
//    itoa( setHeading, headingString, 10 );
//    setHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    if(setHeading > 99)
//      setHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      setHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      setHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    epd.DisplayFrame(setHome.GetImage(), true);
//    epd.Sleep();
//    Serial.println("SET HEADING");
//    buttonStates[0] = 2;
//  }
//  else if(wantedButtonStates(3,0,0,0)){ //HOLD TILLER POSITION
//    epd.Init(); //regular refreshes, 0.82 seconds
//    holdHome.Clear(UNCOLORED);
//    std::copy_n(baseHome_Image, 5800, holdHome_Image);
//    holdHome.DrawStringAt(162,50,  "HOLD", &Font24, COLORED);
//    holdHome.DrawStringAt(13,115, "SET", &Font24, UNCOLORED);
//    ToHeading();
//    itoa( setHeading, headingString, 10 );
//    holdHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    if(setHeading > 99)
//      holdHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      holdHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      holdHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    currentlyActive = 0;
//    epd.DisplayFrame(holdHome.GetImage(),true);
//    epd.Sleep();
//    Serial.println("HOLD TILLER POSITION");
//    buttonStates[0] = 0;
//  }
//  else if(wantedButtonStates(0,1,0,0)){ //NOT SET, PRESS DOWN 15
//    //
//    Serial.println("TRYING TO GO DOWN 15");
//    buttonStates[1] = 0;
//  }
//  else if(wantedButtonStates(0,0,1,0)){ //NOT SET, PRESS UP 15
//    //
//    Serial.println("TRYING TO GO UP 15");
//    buttonStates[2] = 0;
//  }
//  else if(wantedButtonStates(2,1,0,0)){ //WHEN SET, DOWN 15
//    epd.Init(); //regular refreshes, 0.82 seconds
//    setHome.Clear(UNCOLORED);
//    std::copy_n(baseHome_Image, 5800, setHome_Image);
//    setHome.DrawStringAt(162,50,  "ACTIVE", &Font24, COLORED);
//    setHome.DrawStringAt(5,115, "HOLD", &Font24, UNCOLORED);
//    updateHeading(-15);
//    itoa( setHeading, headingString, 10 );
//    setHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    if(setHeading > 99)
//      setHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      setHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      setHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    epd.DisplayFrame(setHome.GetImage(), true);
//    epd.Sleep();
//    Serial.println("WHEN SET, DOWN 15");
//    buttonStates[1] = 0;
//  }
//  else if(wantedButtonStates(2,0,1,0)){ //WHEN SET, UP 15
//    epd.Init(); //regular refreshes, 0.82 seconds
//    setHome.Clear(UNCOLORED);
//    std::copy_n(baseHome_Image, 5800, setHome_Image);
//    setHome.DrawStringAt(162,50,  "ACTIVE", &Font24, COLORED);
//    setHome.DrawStringAt(5,115, "HOLD", &Font24, UNCOLORED);
//    updateHeading(15);
//    itoa( setHeading, headingString, 10 );
//    setHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    if(setHeading > 99)
//      setHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      setHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      setHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    epd.DisplayFrame(setHome.GetImage(), true);
//    epd.Sleep();
//    Serial.println("WHEN SET, UP 15");
//    buttonStates[2] = 0;
//  }
//  else if(wantedButtonStates(0,0,0,1)){ //ENTER MENU, HOLD (so not moving)
//    epd.Init(); //regular refreshes
//    std::copy_n(baseBlank_Image, 5800, menuHome_Image);
//    if(setHeading > 99)
//      menuHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      menuHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      menuHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    menuHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    menuHome.DrawStringAt(162,50,  "HOLD", &Font24, COLORED);
//    epd.DisplayFrame(menuHome.GetImage(), true);
//    epd.Sleep();
//    Serial.println("ENTER MENU");
//    buttonStates[3] = 2;
//  }
//  else if(wantedButtonStates(2,0,0,1)){ //ENTER MENU, SET (so moving)
//    epd.Init(); //regular refreshes
//    std::copy_n(baseBlank_Image, 5800, menuHome_Image);
//    if(setHeading > 99)
//      menuHome.DrawCircle(228, 23, 2, COLORED);   //degree symbol
//    else if(setHeading > 9)
//      menuHome.DrawCircle(211, 23, 2, COLORED);   //degree symbol
//    else
//      menuHome.DrawCircle(194, 23, 2, COLORED);   //degree symbol
//    menuHome.DrawStringAt(173,20, headingString, &Font24, COLORED);
//    menuHome.DrawStringAt(162,50,  "ACTIVE", &Font24, COLORED);
//    epd.DisplayFrame(menuHome.GetImage(), true);
//    epd.Sleep();
//    Serial.println("ENTER MENU");
//    buttonStates[3] = 2;
//  }
//  else if(wantedButtonStates(1,0,0,2) || wantedButtonStates(3,0,0,2)){ //ENTER PID, has to check if set or hold 
//    //
//    Serial.println("ENTER PID CHANGES");
//    buttonStates[0]++;
//    buttonStates[3] = 4;  //one level deeper menu, to not trigger exit base menu when in pid menu
//  }
//  else if(wantedButtonStates(4,0,0,5) || wantedButtonStates(2,0,0,5)){ //ENTER PID, has to check if set or hold 
//    //
//    Serial.println("EXIT PID CHANGES");
//    buttonStates[3] = 2;
//  }
//  else if(wantedButtonStates(-1,0,0,3)){ //EXIT MENU might have to add 2 for this for set and hold
//    //
//    Serial.println("EXIT MENU");
//    buttonStates[3] = 0;
//  }
//
//}

int wantedButtonStates( int w,int r, int g, int y){ //-1 means don't care
  if(w == -1)
    w = buttonStates[0];
  if(r == -1)
    r = buttonStates[1];
  if(g == -1)
    g = buttonStates[2];
  if(y == -1)
    y = buttonStates[3];
    
  if(buttonStates[0] != w || buttonStates[1] != r || buttonStates[2] != g || buttonStates[3] != y){
    return 0; //button states DONT match
  }
  return 1; //does match
}

/********************************INTERRUPT ROUTINES********************************/
void interrupt_LeftLeft(){
  noInterrupts();
  interrupt = millis();
  if(interrupt-last_interrupt > 300){
    if(buttonStates[0] % 2 == 0){
      buttonStates[0]++;
    }
  }
  last_interrupt = interrupt;
  interrupts();
}
void interrupt_Left(){
  noInterrupts();
  interrupt = millis();
  if(interrupt-last_interrupt > 300){
    if(buttonStates[1] % 2 == 0){
      buttonStates[1]++;
    }
  }
  last_interrupt = interrupt;
  interrupts();
}
void interrupt_Right(){
  noInterrupts();
  interrupt = millis();
  if(interrupt-last_interrupt > 300){
    if(buttonStates[2] % 2 == 0){
      buttonStates[2]++;
    }
  }
  last_interrupt = interrupt;
  interrupts();
}
void interrupt_RightRight(){
  noInterrupts();
  interrupt = millis();
  if(interrupt-last_interrupt > 300){
    if(buttonStates[3] % 2 == 0){
      buttonStates[3]++;
    }
  }
  last_interrupt = interrupt;
  interrupts();
}
