// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX

float x, y, z;
float total;

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

void setup(void) {

  Serial.begin(9600);
  accSetup();
  BTSetup();
  delay(2000);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
    delay(2000);
}

void loop() {

//  lis.read();      // get X Y and Z data at once

  sensors_event_t event;
  lis.getEvent(&event);


  x = -event.acceleration.x; 
  y = -event.acceleration.y; 
  z = -event.acceleration.z;
  total = sqrt((x * x) + (y * y) + (z * z));

  serialPrint();
  BTPrint();

  delay(300);
}
