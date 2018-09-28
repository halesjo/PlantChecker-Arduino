/*  Automatic pumping system
    This sketch was orignally written by SparkFun Electronics
    Joel Bartlett 
    August 31, 2015
    Adapted by Josie Hales
    August 25, 2018

    This sketch will make a pump water crops if the mositure level is too low in the soil
*/

int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Soil moisture Power pin
int pumpPower = 8;//Pump Relay pin

int level = 0; //level of moisture 1023 = dry, 0 = wet
int threshold = 800; //threshold for water to be pumped
int checkingDelay = 1000; //delay between checking soil moisture level
int pumpingTime = 10000; //length of time pumping water

void setup() 
{
  Serial.begin(9600);   // open serial over USB

  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  digitalWrite(pumpPower, LOW);//Set to LOW so no power is flowing to the pump relay
}

void loop() 
{
Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
level = readSoil();
Serial.println(level);
checkLevel(level);

delay(checkingDelay);//take a reading every second
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
  if(level > threshold){
    digitalWrite(pumpPower, HIGH);//turn D8 "On"
    delay(pumpingTime);
    digitalWrite(pumpPower, LOW);//turn D8 "Off"
  }

}
