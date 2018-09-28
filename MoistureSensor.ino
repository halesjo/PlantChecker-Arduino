#include "SevSeg.h"
SevSeg sevseg; 


int val = 0; //value for storing moisture value 
int soilPin = A5;//Declare a variable for the soil moisture sensor 
int soilPower = 13;//Soil moisture Power pin
int counter = 0;
int pumpPower = 0;//Pump Relay pin

int level = 0; //level of moisture 1023 = dry, 0 = wet
int threshold = 550; //threshold for water to be pumped
int checkingDelay = 5000; //delay between checking soil moisture level
int pumpingTime = 5000; //length of time pumping water

void setup(){
  byte numDigits = 4;
  byte digitPins[] = {9, 10, 11, 12};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(soilPower, OUTPUT);//Set D0 as an OUTPUT
  pinMode(pumpPower, OUTPUT);//Set as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  digitalWrite(pumpPower, LOW);//Set to LOW so no power is flowing to the pump relay
}

void loop(){
    Serial.print("Soil Moisture = ");    
    //get soil moisture value from the function below and print it
    level = readSoil();
    Serial.println(level);
    checkLevel(level);
    counter = checkingDelay;
    while (counter > 0)
    {
      sevseg.setNumber(level);
      sevseg.refreshDisplay(); 
      delay(5);
      counter--;
    }
    
}

//This is a function used to get the soil moisture content
int readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
void checkLevel(int level)
{
  while(level > threshold){
    digitalWrite(pumpPower, HIGH);//turn D8 "On"
    delay(pumpingTime);
    level = readSoil();
  }
  digitalWrite(pumpPower, LOW);//turn D8 "Off"
  delay(5);
  level = readSoil();
}
