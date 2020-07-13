#ifndef __GPIO_H__
#define __GPIO_H__

#include <xc.h>
typedef enum
{
   PORT_A,
   PORT_B,
   PORT_C,
   PORT_D,
   PORT_E
}tPort;

typedef enum
{
    GPIO_OUT = 0,
    GPIO_IN = 1
}tPortDirection;

void GPIO_InitPortPin(tPort port, unsigned char pin, tPortDirection direction);
void GPIO_InitPort(tPort port, tPortDirection direction);
void GPIO_Update(void);
void GPIO_SetPortPinState(tPort port, unsigned char pin, unsigned char state);
void GPIO_SetPortState(tPort port, unsigned char state);
unsigned char GPIO_GetPortPinState(tPort port, unsigned char pin);
#endif // __GPIO_H__