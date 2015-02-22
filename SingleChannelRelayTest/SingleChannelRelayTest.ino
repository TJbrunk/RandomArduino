
const int relay = 9; // PWM output pin#9
const int on = 0; //need to write 0 to a PWM pin to turn off the relay
const int off = 255; //need to write 255 to PWM pin to turn on the relay

/**********************************************SETUP*************************************************/
void setup()
{
Serial.begin(9600);
//pinMode (relay, OUTPUT); //set pin 9 as an output pin
}

/***************************************************MAIN****************************************************/
void loop()
{
analogWrite (relay, 0);
Serial.print("Output is at 0 \n");
delay (2000);
analogWrite (relay, 255);
Serial.print("Output is at 255 \n");
delay (2000);
}
