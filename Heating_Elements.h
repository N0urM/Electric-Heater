#ifndef HEATING_ELEMENTS_H
#define	HEATING_ELEMENTS_H

#define HEATING_MODE    1
#define NO_HEATING_MODE 2
#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"
#include "gpio.h"
#include "ADC.h"
#include "Electrical_Heater.h"

/*--------------------Notes-----------------------------------------
 * This Module is responsible for communicating with the 
 * Heating elements Prephirals which include:
 *  - Heating Element (Heater)
 *  - Cooling element (Fan)
 *  - Heating LED
 *  - Heating sensor LM35 
 ------------------------------------------------------------------*/


// ------ Public function prototypes -------------------------------
void Heating_Elements_init();   //initialize module
void Heating_Elements_Update(void);
void set_heating_mode(tByte);
tByte get_Avg_Temp ();

#endif	

