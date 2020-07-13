#ifndef         HEATER_H
#define         HEATER_H

#include <xc.h>
#include "main.h"
#include "Seg7.h"
#include "Ext_E2PROM.h"
#include "push_button.h"
#include "Heating_Elements.h"

/*--------------------Notes-----------------------------------------
 * This Module Represents the Surface layer directly communicating 
 * with the the Scheduler and acting upon HW via other modules/drivers
 ------------------------------------------------------------------*/

// ------ Public constants -----------------------------------------
#define OFF_STATE 0
#define ON_DISPLAY_STATE 1
#define ON_SETTING_STATE 2

#define SETTING_MODE     0
#define SETTINGP         1
#define SETTINGM         2
#define INITIAL_TEMP    60

// ------ Public function prototypes -------------------------------
void EH_Init();
void EH_Update (void);
tByte Get_Setting_Temp();

#endif