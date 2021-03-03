float value = -43.39;
float valfloat;
String valtxt = "";

#define EEPROM_ADD 0
#include <AT24C256.h>

AT24C256 eeprom = AT24C256();

void setup() {
  Serial.begin(9600);
}

void loop() {

  //*********************************WRITE DATA***************************************

  //convert float to string
  valtxt =(String)value;

  //print every char
  for(int i= EEPROM_ADD; i<valtxt.length()+EEPROM_ADD; i++)
  {
    Serial.println("valtxt[" + (String)i+ "] : " + (String)valtxt[i-EEPROM_ADD]);
  }

  //print every char to a different address.
  for(int i = EEPROM_ADD; i<valtxt.length()+1+EEPROM_ADD; i++)
  {
    //if value is negative then write 0 at the address 0 
    if(i == EEPROM_ADD)
    {
      if(value<0)
      {eeprom.write(0, i);}
      else
      {eeprom.write(1, i);}
    }
    //else write numbers from the float conversion
    else
    {
      //write 10 when encoutering a dot in the float
      if((String)valtxt[i-EEPROM_ADD] == ".")
        {eeprom.write(10, i);}
      else 
      //i have no idea why i have to substract 48, but it works that way. 
      {eeprom.write(valtxt[i-EEPROM_ADD]-48, i);}
    }

    
    if (i == valtxt.length()+EEPROM_ADD)
    {
      eeprom.write(254, i);
    }  
  }

  //************************************READ DATA*****************************


  //create a boolean val to exit while loop
  boolean resume = false;

  //serial.print every char saved until = 254 (end of the number)

  for(int i = EEPROM_ADD; eeprom.read(i) < 254; i++)
  {
    Serial.println("Lecture sur add " + (String)i+ " : " + (eeprom.read(i)));
  }
  
  String val;
  while(resume == false)
  {
    //if first char is 0, then add "-" in val
    if(eeprom.read(EEPROM_ADD) == 0)
    {
      val = val + "-";
    }

    //write char until the end of number
    for(int i=1+EEPROM_ADD; eeprom.read(i) < 254;i++)
    {
      //manage the dot of the float
      if(eeprom.read(i)==10)
      {
        val = val + ".";
      }
      else
      {
        val = val +String(eeprom.read(i));
      }
    }
    //print completed string and exit while
    Serial.println("val : " + val);
    resume = true;
  }

  //convert from string to float and print
  valfloat = val.toFloat();
  Serial.println("valfloat : " + String(valfloat));
  delay(5000);
}
