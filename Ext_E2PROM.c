#include "Ext_E2PROM.h"


void EXT_E2PROM_Init ()
{
     I2C_Init(100000);         // initialize I2C communication
}

tByte EXT_E2PROM_Read(tByte Adress){
  tByte data_d;
  I2C_Start();              // issue I2C start signal
  I2C_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C_Wr(Adress);           // send byte (data address)
  I2C_Start();              // issue I2C signal repeated start
  I2C_Wr(0xA3);             // send byte (device address + R)
  data_d = I2C_Rd(0u);      // Read the data (NO acknowledge)
  I2C_Stop();               // issue I2C stop signal
  return data_d;
}

void EXT_E2PROM_Write(tByte Adress , tByte Data){
  I2C_Start();              // issue I2C start signal
  I2C_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C_Wr(Adress);          // send byte (address of EEPROM location)
  I2C_Wr(Data);             // send data (data to be written)
  I2C_Stop();               // issue I2C stop signal
}