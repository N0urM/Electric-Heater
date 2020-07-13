#ifndef EXT_E2PROM_H
#define EXT_E2PROM_H
#include <xc.h>
#include "main.h"
#include "I2C.h"

// ------ Public constants -----------------------------------------
#define BYTE_ADDRESS 0x00

// ------ Public function prototypes -------------------------------
void  EXT_E2PROM_Init();
tByte EXT_E2PROM_Read(tByte Adress);
void EXT_E2PROM_Write(tByte Adress , tByte Data);

#endif