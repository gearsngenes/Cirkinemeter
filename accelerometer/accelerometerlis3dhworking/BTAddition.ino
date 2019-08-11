void BTSetup ()

{
  BTSerial.begin(9600);
  BTSerial.println("BT Demo");

}

void BTPrint()
{

  BTSerial.print("X: "); BTSerial.print(x ); BTSerial.print("  ");
  BTSerial.print("Y: "); BTSerial.print(y ); BTSerial.print("  ");
  BTSerial.print("Z: "); BTSerial.print(z); BTSerial.print("  ");
  BTSerial.println("m/s^2 ");

  BTSerial.println("----------");
 // BTSerial.print("Total: "); BTSerial.print(total); BTSerial.print("  "); BTSerial.println("m/s^2 ");

}
