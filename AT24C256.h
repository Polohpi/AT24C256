#ifndef AT24C256_h
#define AT24C256_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define EEPROM_I2C_ADDRESS 0x50

class AT24C256 {
  public:

  AT24C256();

  void Ecriture(byte val, int address);
  int Lecture(int address);
  

  private:
  
};

#endif
