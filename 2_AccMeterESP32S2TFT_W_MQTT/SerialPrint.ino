void serialPrint()
{
  
  Serial.print("\t\tX: "); Serial.print(accx);
  Serial.print(" \tY: "); Serial.print(accy); 
  Serial.print(" \tZ: "); Serial.print(accz); 


  Serial.println(" m/s^2 ");


//Serial.print("\tTotal:"); Serial.print(total);Serial.println(" m/s^2");
  Serial.println();
}
