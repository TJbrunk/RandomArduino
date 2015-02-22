
const int relay = 9; // Digital output pin#8

/**********************************************SETUP*************************************************/
void setup()
{
Serial.begin(9600);
pinMode (relay, OUTPUT); //set pin 9 as an output pin
}

/***************************************************MAIN****************************************************/
void loop()
{
digitalWrite (relay, HIGH);
Serial.print("Output is at HIGH \n");
delay (2000);
digitalWrite (relay, LOW);
Serial.print("Output is at LOW \n");
delay (2000);
}
