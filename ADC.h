#ifndef    ADC_H
#define    ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"

// Function prototypes 
void  ADC_init();
void  ADC_Sample();
tByte ADC_Read(tByte Channel);


#endif	

