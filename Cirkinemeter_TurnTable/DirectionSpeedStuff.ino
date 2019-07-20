void controlSpeedDirection(){
  uint32_t buttons = ss.readButtons();
  
  uint16_t color;
  color=ST77XX_WHITE;
  tft.setCursor(0,50);
  tft.print("Speed: ");tft.print(motorSpeed);
  //tft.setCursor(50,20);
  //tft.print("Omg:");tft.print(omega);
  
  analogWrite(pwm,motorSpeed);
  
  color = ST77XX_BLACK;

  //direction action 1
  if (! (buttons & TFTWING_BUTTON_RIGHT)) {
    CCW();
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("COUNTERCLOCKWISE");
    color = ST77XX_WHITE;
    tft.setCursor(0,80);
    tft.print("CCW");
    
  }
  //direction action 2
  
  if (! (buttons & TFTWING_BUTTON_LEFT)) {
    CW();
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("CLOCKWISE");
    color = ST77XX_WHITE;
    tft.setCursor(0,80);
    tft.print("CW");
    
  }
  
  
  color = ST77XX_BLACK; // see if you can optimize the blacks  do we even need it.
  
  
  
  //Speed action 3
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_DOWN)) {
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("SLOW DOWN");
    motorSpeed-=5;
    if(motorSpeed<0){
      motorSpeed=0;
    }
    Serial.print("Speed: ");Serial.println(motorSpeed);
    color = ST77XX_WHITE;
    tft.fillScreen(ST77XX_BLACK);
  }
  
  
  tft.setCursor(0,50);
  tft.print("Speed: ");tft.print(motorSpeed);

  //Speed action 4
  color = ST77XX_BLACK;
  if (! (buttons & TFTWING_BUTTON_UP)) {
    
    Serial.println("SPEED UP");
    motorSpeed+=5;
    if(motorSpeed>255){
      motorSpeed=255;
    }
    
    Serial.print("Speed: ");Serial.println(motorSpeed);
    color = ST77XX_WHITE;
    tft.fillScreen(ST77XX_BLACK);
  }
  
  
  tft.setCursor(0,50);
  tft.print("Speed: ");tft.print(motorSpeed);
  
  
  
  color = ST77XX_BLACK;
  //Stop action 5
  if (! (buttons & TFTWING_BUTTON_SELECT)) {
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("STOP");
    motorSpeed=0;
    Serial.print("Speed: ");Serial.println(motorSpeed);
    color = ST77XX_WHITE;
    //fSTOP();
  }
  
  if(count==maxCount){
    calcRPS();
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0,20);
    tft.print("w: ");tft.print(omega);
  }
}
