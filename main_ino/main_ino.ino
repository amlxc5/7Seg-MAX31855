/*************************************************** 
 This is an example of reading data from a thermocouple amplifier and displaying it on a 4 digit 7-segment display.
 
 There is a Adafruit MAX31855 Breakout wired to a Arduino Nano via SPI.
 There is a Sparkfun 7-segment serial display wired via I2C with an address of 0x71. 
 
 7-segment commands can be found on Sparkfun's wiki: https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands
 
 The display supports 3 decimal LEDs. this work s out great for my 
 application since the temp reading from the MAX31855 is a double. 
 I can represent the decimal place for the float (double).
 The command sequence for sending the value should be:
 1) Send 0x76 to clear the screen
 2) Send 0x71 to enter decimal control mode
 3) If  (0x00000000 
 
 As the temp gets larger we will only care about 4 or less significant digits. Why? That's all the display can handle silly!
 Okay, so we need to write out a method for finding how many sigfigs we have. The temp will be a double. *I think I can change that*. 
 Totally assuming here, the max value we will be seeing in that double is "1350.00". This is the max value supported by a K-type thermocouple. 
 I'll need to check the datasheet for the max31855 and see what happens if the value of the thermocouple is a higher than that? does it cap off , throw an error?
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
 Wire.write("v"); //Clear the display screen with command code 0x76
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

void Serial7::print(float value)
{
  int output = 0;
  
  // decimal point control character
  Wire.write(0x77);
  
  // switch depending on value
  if(value < 10) {
    Wire.write(0x01);
    output = value*1000;
  }
  else if(value < 100) {
    Wire.write(0x02);
    output = value*100;
  }
  else if(value < 100) {
    Wire.write(0x04);
    output = value*10;
  }
  else {
    Wire.write(0x08);
	output = value;
  }
  
  // output four least significant bits
  Wire.print(output/1000 % 10, HEX);
  Wire.print(output/100 % 10, HEX);
  Wire.print(output/10 % 10, HEX);
  Wire.print(output % 10, HEX);
}
