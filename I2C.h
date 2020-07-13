#ifndef I2C_H
#define	I2C_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "gpio.h"
#include "main.h"

// function prototypes 
void I2C_Init(tLong Freq);
void I2C_Start();
void I2C_Re_Start();
void I2C_Busy();
void I2C_Stop();
void I2C_Wr(tByte data);
tByte I2C_Rd(tByte);

#endif	

