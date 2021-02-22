//This Library is used to communicate with an AT24CXXX type (256 here) chip
//The i2c address can be modified in AT24C256.h


#include <Wire.h> //I2C library
#include "AT24C256.h"

//Create Object
AT24C256 eeprom = AT24C256();

//this val will be wrote the the chip. An int is used here.
int val = 24;

//The address on wich val will be wrote
int Add = 0;

void setup() 
{
  //Start Serial and i2c
  Serial.begin(9600);
  Wire.begin();
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() 
{
  //Write val to the address
  Serial.println("Writing of " + (String)val + " on " + (String)Add);
  eeprom.write(val, Add);

  //print the val read in the address specified and print it to serial
  Serial.println(eeprom.read(Add));

  //Stop
   while(1);
} 
