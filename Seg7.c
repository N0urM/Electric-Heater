#include "Seg7.h"

//-----------Private Variables------------
static tByte flag = 0;
static tWord tick_counter = 0;
static tByte n1 , n2;
static const tByte table[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71};
static tByte Seg_mode = OFF_MODE;
// ------------Functions------------------

/*
 Initialize Ports and pins for Display 
 */
void Seg7_Init(){
     GPIO_InitPort(PORT_D , GPIO_OUT );
     GPIO_SetPortState(PORT_D , 0);
     GPIO_InitPortPin(PORT_A, Dis_1_pin, GPIO_OUT);
     GPIO_InitPortPin(PORT_A, Dis_2_pin, GPIO_OUT);
     GPIO_SetPortState(PORT_A , 0);
}

void set_Seg_mode (tByte mode){
    Seg_mode = mode;
}

/*
 Main Display Task run by the Scheduler
 */
void Seg7_Update(void){
     switch (Seg_mode){
       case UPDATE_MODE:
       {
            if(flag == 0)
            {
              flag = 1;
              GPIO_SetPortPinState(PORT_A, Dis_1_pin , 0);
              GPIO_SetPortPinState(PORT_A, Dis_2_pin , 1);
              GPIO_SetPortState(PORT_D, table[n2] );
            }
            else if(flag == 1)
            {
               
              flag = 2;
              GPIO_SetPortPinState(PORT_A, Dis_2_pin , 0);
              GPIO_SetPortPinState(PORT_A, Dis_1_pin , 1);
              GPIO_SetPortState(PORT_D, table[n1] );
            }
            else if(flag == 2) // Prevent Flickering in display
            {
              flag = 0;
              GPIO_SetPortPinState(PORT_A, Dis_2_pin , 0);
              GPIO_SetPortPinState(PORT_A, Dis_1_pin , 0);
             
            }
           
            break;
       }
       case OFF_MODE:
       {
          GPIO_SetPortPinState(PORT_A, Dis_1_pin , 0);
          GPIO_SetPortPinState(PORT_A, Dis_2_pin , 0);
          break;
       }
       case BLINK_MODE:
       {    if (++tick_counter < BLINK_PERIOD){
               GPIO_SetPortPinState(PORT_A, Dis_1_pin , 0);
               GPIO_SetPortPinState(PORT_A, Dis_2_pin , 0);
            }else {
               tick_counter = 0;
               Seg_mode =  UPDATE_MODE;
            }
             break;
       }
     }
}
// ----Setters and Getters section--------------

void Set_Seg7 (tByte b1 , tByte b2){
    n1 = b1;
    n2 = b2;
}

tByte Get_Seg7 (){
    return  (n1 + (10*n2));
}

//End of File