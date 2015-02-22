//Outputs:
int red = 12;
int yellow = 13;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(yellow, false);
  digitalWrite (red, true);
  Serial.println("Red LED is on");
  delay(500);
  digitalWrite (red, false);
  digitalWrite (yellow, true);
  Serial.println("Yellow LED is on");
  delay(500);
}
