#include "Wire.h"
const int address = 0x4a; //Address of TC74A2 digital temp sensor
const float setpoint = 29;//18.33; //in *C (18.33*C = 65*F)
const int baudrate = 9600; //serial communication rate
const byte db = 1; //*c deadband
const int relayPin = 12;
const byte high = setpoint + db;
const byte low = setpoint - db;

byte val = 0; //var to hold value read from i2c bus
int tempC;    //temperature in a byte
//uint_t relay = LOW; //var to hold value of the relay (True/False)(Open/Closed)
boolean inDB = false;
boolean on = LOW;
boolean off = HIGH;
String debug = "";

void setup()
{
    Wire.begin();
    Serial.begin(baudrate);
    pinMode(relayPin, OUTPUT);
}

void loop()
{
    Wire.beginTransmission(address);
    //start the transmission

    //Tell the sensor to send data
    Wire.write(val);

    Wire.requestFrom(address, 1);
    if (Wire.available()) {
        tempC = Wire.read();
        // temp is above the setpoint window, and we haven't gone below the SP yet: turn on the fridge
        if (tempC >= low && !inDB){
            digitalWrite (relayPin, on);
     //       debug = "Case1: Temp: "+tempC +" Low: "+low+" inDB: "+!inDB;
            Serial.println("Case1");
            Serial.println(tempC);
    //        Serial.println('Temp: ' %d' Low: '%s  tempC);
        }
        //temp is below the SP window: Turn off the fridge && set the inDB
        else if (tempC <= low){
          inDB = true;
          digitalWrite (relayPin, off);
          Serial.println("Case2");
          Serial.println(tempC);
        }
        //temp has gone above the SP window: reset inDB && fridge on
        else if (tempC >= high){
          inDB = false;
          digitalWrite (relayPin, on);
          Serial.println("Case3");
          Serial.println(tempC);
        }
    }
//    Serial.println(debug);
    else {
        Serial.println("---");
    }
    delay(5000);
}
