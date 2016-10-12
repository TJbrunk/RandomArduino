#define FREQ_LED    (unsigned long)160
#define FREQ_MAGNET  (unsigned long)80

boolean magnet_on;
boolean pulse_magnet = true;
int target = 5;

/************************************************* Magnet Module ************************************************/
void MagnetOn()
{
  PORTB &= ~(1 << PORTB0);
  PORTB |= (1 << PORTB1);
//  Serial.print(" -ON- ");
}

void MagnetOff()
{
  PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
//    Serial.print(" -OFF- ");
}

void Magnet_InitPins()
{
  // Set PB1 and PB2 as outputs
  // Arduino Mege 53 & 52
  DDRB |= (1 << DDB1)|(1 << DDB0);
}

void Magnet_InitTimer()
{
    // Clear timer registers
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3  = 0;
    
    // 16MHz/8/160Hz
    // Clock_Freq/Prescaler/Frequency
    //Set compare register match
    OCR3A = (unsigned long)16000000 / (unsigned long)8 / 80;            
    TCCR3B |= (1 << WGM12);   // CTC mode
  
    // 8 prescaler
    TCCR3B |= (1 << CS11);   
    
    // enable timer compare interrupt
    TIMSK3 |= (1 << OCIE1A);  
}

// Timer 1 B compare interrupt used for moving the object
ISR(TIMER3_COMPA_vect)
{
    if(pulse_magnet == true)
    {
        if(magnet_on)
        {
          MagnetOff();
          magnet_on = false;
        }
        else
        {
          MagnetOn();
          magnet_on = true;
        }
    }
}

void Magnet_Init()
{
    Magnet_InitPins();
    Magnet_InitTimer();
    
    magnet_on = false;
}


/************************************************* LED Module ************************************************/
void Led_InitPins()
{
    // led array on pin PB5 (arduino 12)
  DDRB |= (1 << DDB5);
}

void Led_InitTimer()
{
  // Clear timer registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // 16MHz/8/160Hz
  // Clock_Freq/Prescaler/Frequency
  //Set compare register match
  OCR1A = (unsigned long) 16000000 / (unsigned long) 8 / FREQ_LED;          
  TCCR1B |= (1 << WGM12);   // CTC mode

  // 8 prescaler
  TCCR1B |= (1 << CS11);
  // 256 prescaler  
  //  TCCR1B |= (1 << CS12);     
  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);  
}

// Timer 1 A compare interrupt used for toggling the LEDs
ISR(TIMER1_COMPA_vect)
{ 
    // toggle the LEDs on every interrupt
    PINB |= (1 << PINB5);
}

void Led_Init()
{
  Led_InitPins();
  Led_InitTimer();
}


/************************************************* Arduino Stuff ************************************************/

void setup()
{
  // disable all interrupts during initalization
  noInterrupts();           
  Led_Init();
  
  Magnet_Init();
  
  // enable all interrupts
  interrupts();

  
  Serial.begin(9600);
}

void loop()
{
  char cmd;
  
  if(Serial.available())
  { 
    cmd = Serial.read();
    switch(cmd)
    {
        case('o'):
        {
            pulse_magnet = false;
            MagnetOn();
            Serial.println("Magnet ON");
            break;
        }
        case('f'):
        {
            pulse_magnet = false;
            MagnetOff();
            Serial.println("Magnet OFF");
            break;
        }
        case('p'):
        {
          if(pulse_magnet)
          {
            pulse_magnet = false;
            Serial.println("Pulsing OFF");
            break;
          }
          else
          {
            pulse_magnet = true;
            Serial.println("Pulsing ON");
            break;
          }
        }
        case('+'):
        {
            target++;
            Serial.print("Target count: ");
            Serial.println(target);
            break;
        }
        case('-'):
        {
            target--;
            Serial.print("Target count: ");
            Serial.println(target);
            break;
        }
        default:
        {
          Serial.println("Unknown command");
        }
    }
  }
}

