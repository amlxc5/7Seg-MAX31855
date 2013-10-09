/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MAX31855.h"
#include <Wire.h>
int thermoDO = 5;
int thermoCS = 4;
int thermoCLK = 3;
#define DISPLAY_ADDRESS1 0x71 //This is the default address of the OpenSegment with both solder jumpers open

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
  
void setup() {
  Serial.begin(9600);
  Wire.begin(); //Join the bus as master
  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  Wire.beginTransmission(DISPLAY_ADDRESS1);
  Wire.write('v');
  Wire.endTransmission();
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double F = thermocouple.readFarenheit();
   if (isnan(c)) {
     i2cSendError();
   } else {
     i2cSendValue(c);
     }
   
 
   delay(1000);
}

void i2cSendValue()
{
 Wire.beginTransmission(DISPLAY_ADDRESS1); //transmit to device #1
 Wire.
 }

void i2cSendValue(int tempTransmission)
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write(tempCycles / 1000); //Send the left most digit
  tempCycles %= 1000; //Now remove the left most digit from the number we want to display
  Wire.write(tempCycles / 100);
  tempCycles %= 100;
  Wire.write(tempCycles / 10);
  tempCycles %= 10;
  Wire.write(tempCycles); //Send the right most digit
  Wire.endTransmission(); //Stop I2C transmission
}
