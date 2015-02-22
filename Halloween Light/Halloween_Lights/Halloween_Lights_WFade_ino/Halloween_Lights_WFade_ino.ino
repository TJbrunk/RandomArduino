/*******************************Globals**************************************************/
// Outputs:
int RY[2]={9,10}; // Red:9 yellow:10

//VARIABLES:
byte RYValues[2]={0,0};
int red = 0;
int yellow = 1;
boolean DEBUG = false;

int StepSize = 5;
int StepDelay = 250;

//Functions:
void WriteOutputValues(){  //declare a global function
   for(int i=0; i<sizeof(RY); i++){
    analogWrite (RY[i], RYValues[i]);
  }
}

/**********************************************SETUP*************************************************/
void setup()
{
  for(int i=0; i<2; i++){
    pinMode(RY[i], OUTPUT);// sets the pins as output
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
  FadeIn(yellow);
  FadeOut(red);
  FadeOut(yellow);
}

void FadeIn(int color)
{
  while (RYValues[color] < 255)
  {
   RYValues[color] = RYValues[color] + StepSize;
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
  while (RYValues[color] > 0)
  {
   RYValues[color] = RYValues[color] - StepSize;
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
  Serial.print(RYValues[red]);
  Serial.print("\t Yellow:");
  Serial.println(RYValues[yellow]); //print output values to serial port
}
