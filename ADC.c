#include "ADC.h"

void  ADC_init(){
    // Enable ADC 
    // Clock = Fosc / 8
    // conversion time 1 micro sec 
    // Result is right Justified
    ADCON0 = 0x41;
    ADCON1 = 0x80;
    
}

tByte ADC_Read(tByte Channel){
    ADCON0 |= Channel<<3; // Select channel
    ADCON0 |= 0x04;       // Start Conversion
    while (ADCON0 & 0x04);
    return ( (ADRESH<<8) + ADRESL);
}

