#include "AT24C256.h"
#include <Wire.h>

AT24C256::AT24C256()
{ 
  
}

void AT24C256::Ecriture (byte val, int address ) 
{
  Serial.println("Ecriture de " + String(val) + " sur " + String(address));
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write(address & 0xFF); // LSB
  
   
  Wire.write(val);
  Wire.endTransmission();

  delay(5);
}

int AT24C256::Lecture(int address ) 
{
  byte rData = 0xFF;
 
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();  

  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  

  rData =  Wire.read();

  return rData;
}
