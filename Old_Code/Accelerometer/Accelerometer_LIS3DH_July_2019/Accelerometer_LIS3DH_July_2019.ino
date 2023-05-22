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


  x = event.acceleration.x; 
  y = event.acceleration.y; 
  z = event.acceleration.z;
  total = sqrt((x * x) + (y * y) + (z * z));

  serialPrint();
  BTPrint();

  delay(300);
}

//--------------------------LIBRARIES (NECESSARY)------------------------------------
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
//-----------------------------------------------------------------------------------
SoftwareSerial BTSerial(10, 11); // Associates pins 10 and 11 on the Feather with the Recieve and Transmit, RESPECTIVELY
//-----------------------------------------

//--------ESTABLISH I2C (Make accelerometer give data through SCL and SDA pins-----------
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
#if defined(ARDUINO_ARCH_SAMD)
//---------------------------------------------------------------------------------------

//-------------------------------Necessary Define Statements for USB
#define Serial SerialUSB
#endif
//------------------------------

//--------------------------VARIABLE DECLARATIONS--------------------------
float x, y, z;//Declares x,y, and z accelerations as floats (decimal values)
float total;  //Vector sum of all three accelerations (phythagorean theorem and force components): total = sqrt(x^2+y^2+z^2)
//--------------------------------------------------------------------------

//VOID SETUP runs code in it ONCE, for initial conditions
void setup(void) {
  Serial.begin(9600);//allows one to send data from the arduino to the COMPUTER(through a screen called SERIAL MONITOR)
  
  accSetup();//See code labeled: AccBasic ()
  BTSetup();//See code labeled: BTAddition(Connects to Bluetooth)
  
  delay(2000);//Wait 2 seconds
  // delay() measures time in milliseconds (2000=2000 milliseconds=2 seconds).
  
 //--------------------Prints the Name of Code and the Date it is running------------------------------
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");
 //----------------------------------------------------------------------------------------------------
    delay(2000);
}

//VOID LOOP CONTINOUSLY runs code in it
void loop() {

  //  lis.read();      // get X Y and Z data at once
  
//------------Sets up the Accelerometer sensors--------------------------
  sensors_event_t event;
  lis.getEvent(&event);
//-----------------------------------------------------------------------

//---------------------Physics Calculations--------------------------
  x = event.acceleration.x; //Get the x acceleration from accelerometer
  y = event.acceleration.y; //Get the y acceleration from accelerometer
  z = event.acceleration.z; //Get the z acceleration from accelerometer
  total = sqrt((x * x) + (y * y) + (z * z)); //Get the Vector Sum magnitude of the accelerations through PYTHAGOREAN THEOREM
//-------------------------------------------------------------------
  serialPrint();//Print all accelerations and Vector sum to the Computer's SERIAL MONITOR
  BTPrint();//Send data to HC-06 (Which in turn, sends data to SMARTPHONE)

  delay(100);//Publish data every 1/10 seconds
}
