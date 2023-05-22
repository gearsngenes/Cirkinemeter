#include <SPI.h>
#include <Wire.h>
/**
    Code for ESP32-S2-TFT-Reverse
*/
#include <Arduino.h>
#include "Adafruit_MAX1704X.h"

#include <Adafruit_BME280.h>
#include <Adafruit_ST7789.h>
#include <Fonts/FreeSans12pt7b.h>

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas(240, 135);

// variable for when omega updates
boolean updateOmg = false;


/*
   Code for turntable components
*/
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
int m_speed = 100;
uint8_t idx = 0;
String dirs[] = {"Counter Clock", "Clockwise", "STOP"};


void setup() {
  Serial.begin(115200);

  /**
     Motor Shield setup
  */
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(m_speed);
  // Set direction forward
  myMotor->run(FORWARD);

  /**
     IR Sensor Setup
  */
  IRSetup();

  /**
     OLED setup
  */
  delay(100);


  display.init(135, 240);           // Init ST7789 240x135
  display.setRotation(3);
  canvas.setFont(&FreeSans12pt7b);
  canvas.setTextColor(ST77XX_WHITE);

  Serial.print(F("Found MAX17048"));
  Serial.print(F(" with Chip ID: 0x"));


  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);

  // text display tests
  canvas.fillScreen(ST77XX_BLACK);
  canvas.setCursor(20, 20);
  canvas.print("GnG Cirkinemeter\nTurn-Table");
  display.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  delay(1000);
  canvas.fillScreen(ST77XX_BLACK);
  display.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
}

/**
   Functions/variables for controlling the robot direction. These
   functions include forward, backward, stop, left, and right.
*/
void CCW() {
  myMotor->run(FORWARD);
}

void CW() {
  myMotor->run(BACKWARD);
}

void force_stop() {
  myMotor->run(RELEASE);
}

void loop() {
  canvas.setCursor(20, 20);
  /**
     If any of buttons A,B,or C are pressed, then
     clear the display and modify the values as
     indicated in their specific sections
  */
  if (!digitalRead(0)) { // if A is pressed
    /**
       If A is pressed, increase speed
       no matter what. Cap out at 255.
    */
    m_speed += 1;
    if (m_speed > 255) {
      m_speed = 255;
    }
    myMotor->setSpeed(m_speed);
    canvas.fillScreen(ST77XX_BLACK);
    delay(5);
  }
  else if (digitalRead(1)) {
    /**
       If B is pressed, then cycle through
       -> CCW -> CW -> Stop ->
    */
    idx += 1;
    idx %= 3;
    if (idx == 0) myMotor->run(FORWARD);
    else if (idx == 1) myMotor->run(BACKWARD);
    else myMotor->run(RELEASE);
    canvas.fillScreen(ST77XX_BLACK);
    delay(300);
  }
  else if (digitalRead(2)) {
    /**
       If Button C pressed, then decrease
       the speed of the motor, floor at 0.
    */
    m_speed -= 1;
    if (m_speed < 0) {
      m_speed = 0;
    }
    myMotor->setSpeed(m_speed);
    canvas.fillScreen(ST77XX_BLACK);
    delay(5);
  }
  /**
     After controlling speed and direction:
       - check for IR sensors
       - if enough revolutions occur
   *      * get RPS/Omega
  */
  IRProcessCrossing();
  printOmegaPeriodically();
  if (updateOmg) {
    /**
       If new omega data needs to be
       displayed, then refresh the
       OLED screen.
    */
    canvas.fillScreen(ST77XX_BLACK);
    updateOmg = false;
  }
  /**
     Display the speed and direction
     on the oled featherwing.
  */
  canvas.setCursor(10, 40);
  if (idx==2) {canvas.setTextColor(ST77XX_RED);}; 
  canvas.println(dirs[idx]);
  canvas.setCursor(10, 70);
  canvas.setTextColor(ST77XX_WHITE);
  canvas.println("Speed: " + (String)m_speed);
  canvas.setCursor(10, 110);
  canvas.setTextColor(ST77XX_YELLOW);
  canvas.println(getStringOmgRPS());
  canvas.setTextColor(ST77XX_WHITE);
  delay(10);
  display.drawRGBBitmap(0, 0, canvas.getBuffer(), 240, 135);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
}
