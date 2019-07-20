/* 
  IR Breakbeam sensor demo!
*/



// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the pushbutton status

void IRsetup() {
  // initialize the LED pin as an output:
  //pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
  Serial.begin(9600);
}

void IRRun(){
  // read the state of the pushbutton value:
  sensorState = digitalRead(SENSORPIN);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    //digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    //digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println("Broken");
    count++;
  }
  lastState = sensorState;
}


void calcRPS(){
  deltaT=millis()-startTime;
  startTime=millis();
  rps=count*1000.0/deltaT;
  omega=theta*rps;
  Serial.print("RPS: ");Serial.print(rps);Serial.print(" Omg: ");Serial.println(omega);
  count=0;
}
