#ifndef SEG7_H
#define SEG7_H

#include <xc.h>
#include "main.h"
#include "gpio.h"

// ------ Public constants -----------------------------------------

#define OFF_MODE        0
#define BLINK_MODE      1
#define UPDATE_MODE     2

#define BLINK_PERIOD       50
#define Dis_1_pin          4
#define Dis_2_pin          5
       
// ------ Public function prototypes -------------------------------
void Seg7_Init();
void Seg7_Update(void);
void Set_Seg7(tByte  , tByte );
tByte Get_Seg7();
void set_Seg_mode(tByte);

#endif