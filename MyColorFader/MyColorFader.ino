/*******************************Globals**************************************************/
// Outputs:
int RGB[3]={9,10,11}; // Red:9 Green:10 BLue:11

//VARIABLES:
byte RGBValues[3]={0,0,0};
int red = 0;
int green = 1;
int blue = 2;
boolean DEBUG = true;

int StepSize = 5;
int StepDelay = 250;

//Functions:
void WriteOutputValues(){  //declare a global function
   for(int i=0; i<sizeof(RGB); i++){
    analogWrite (RGB[i], RGBValues[i]);
  }
}

/**********************************************SETUP*************************************************/
void setup()
{
  for(int i=0; i<3; i++){
    pinMode(RGB[i], OUTPUT);// sets the pins as output
  }
//  WriteOutputValues();

  if (DEBUG) {           // If we want to see values for debugging...
    Serial.begin(9600);  // ...set up the serial ouput 
  }
}

/***************************************************MAIN****************************************************/
void loop()
{
  FadeIn(red);
  FadeIn(green);
  FadeOut(red);
  FadeIn(blue);
  FadeOut(green);
  FadeIn(red);
  FadeOut(blue);
  FadeOut(red);
}

void FadeIn(int color)
{
  while (RGBValues[color] < 255)
  {
   RGBValues[color] = RGBValues[color] + StepSize;
   WriteOutputValues();
   delay (StepDelay);
   if (DEBUG)
   {
     PrintDebugString();
   }
  }
  return;
}

void FadeOut(int color){
  while (RGBValues[color] > 0)
  {
   RGBValues[color] = RGBValues[color] - StepSize;
   WriteOutputValues();
   delay (StepDelay);
   if (DEBUG)
   {
     PrintDebugString();
   }
  }
  return;
}

void PrintDebugString(){
  Serial.print("Red:");
  Serial.print(RGBValues[red]);
  Serial.print("\t Green:");
  Serial.print(RGBValues[green]);
  Serial.print("\t Blue:");
  Serial.println(RGBValues[blue]); //print output values to serial port
}
