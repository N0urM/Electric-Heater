#include <xc.h>
#include <pic16f877a.h>

#include "I2C.h"

// Master initialization 

void I2C_Init(tLong Freq){
    // Set I2C pins as output 
    GPIO_InitPortPin(PORT_C , 3 , GPIO_OUT);
    GPIO_InitPortPin(PORT_C , 4 , GPIO_OUT);
    // Enable SSPEN 
    // SSPM = 1000 = FOSC / (4 * (SSPADD+1))
    SSPCON = 0b00101000;            //SSP Module as Master
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*Freq))-1; //Setting Clock Speed
    SSPSTAT = 0;    
}
void I2C_Start(){
    I2C_Busy();
    //Enable bit SEN of the SSPCON2 register
    SEN = 1; 
}

void I2C_Re_Start(){
    I2C_Busy();
    //RSEN: Repeated Start Condition Enabled bit
    RSEN = 1;
}

void I2C_Stop(){
    I2C_Busy();
    // Enable bit PEN in SSPCON2 register
    PEN = 1;
}
void I2C_Busy(){
    // make sure the IIC is not in progress
    while ((SSPCON2 & 0b00011111)    
           ||(SSPSTAT & 0b00000100)) ; 

}

void I2C_Wr(tByte data){
    I2C_Busy();
    SSPBUF = data;
}


tByte I2C_Rd(tByte a){
    I2C_Busy();
    //RCEN: Receive Enable bit
    RCEN = 1;
    I2C_Busy();
    tByte incoming = SSPBUF ;
    I2C_Busy();
    ACKDT = (a)?0:1;
    ACKEN = 1;
    return incoming;
}
