#include <xc.h>
#include "Heating_Elements.h"

//----------Private Variables ---------------

static tByte Sec_blink_counter = 0;
static tByte index = 0;
static tByte temp_readings[10] = {0};
static tByte avg_temp;
static tByte setting_temp;

// ------ Private functions prototypes ------------------------------
//Sensor reading
tByte read_Temp();              
// Cooler / Heater operation
void adjust_Heater(tByte , tByte);
void Turn_On_Heater();
void Turn_On_Cooler();
void Turn_off_Heater_Cooler();
// Heater LED
void Turn_On_Heating_LED();
void Blink_Heating_LED();
void Turn_Off_Heating_LED();

//--------initialization function -----------------
void Heating_Elements_init(){
     GPIO_InitPortPin(PORT_A , HEATING_SENSOR_PIN , GPIO_IN);
     GPIO_InitPort(PORT_C , GPIO_OUT);
     GPIO_InitPortPin(PORT_B , HEATER_LED_PIN , GPIO_OUT);
     GPIO_SetPortState(PORT_A , 0);
     GPIO_SetPortState(PORT_C , 0);
     ADC_init(); 

}

//----------Main Task ---------------
void Heating_Elements_Update(void){
    
    avg_temp = read_Temp();
    setting_temp = Get_Setting_Temp();
    adjust_Heater(avg_temp , setting_temp); 
}

tByte get_Avg_Temp (){
    return avg_temp;
}
/* ---------- Read Temp -------------------------------
   This routine handles the new reading from ADC
   ,update of the latest read values
   and calculate the new Average
---------------------------------------------------------*/

tByte read_Temp(){
      tWord result , sum;
      float volt;
      tByte i , avg;
      result = ADC_Read(HEATING_SENSOR_CHANNEL);
      volt = result*4.89;
      if (index > 9 )index  = 0;
      temp_readings[index] = (volt/10);
      sum = 0;
      for(i=0 ; i< 10 ; i++){
         sum += temp_readings[i];
      }
      index++;
      avg = sum / 10;
      return avg;
}
/* ------ Adjust Heater -------------------------------
   This routine is responsible for interfacing with the
   heating / cooling elements depending on the difference
   between average temperature and user set temp
---------------------------------------------------------*/
void adjust_Heater(tByte avg , tByte set){
      if (avg - set >= 5 ){            // Turn on Cooler
          Turn_On_Cooler();
          Sec_blink_counter = 0 ;
          Turn_On_Heating_LED();
     }
     else if (set - avg >= 5 ){       // Turn on Heater
          Turn_On_Heater();
          Blink_Heating_LED();
     }else {                           // Stop heating/Cooling
           Turn_off_Heater_Cooler();
           Sec_blink_counter = 0;
           Turn_Off_Heating_LED();
     }
}
//-------------Heater/Cooler Section ------------------------

void Turn_On_Heater(){
    GPIO_SetPortPinState(PORT_C , COOLER_PIN , 0);
    GPIO_SetPortPinState(PORT_C , HEATER_PIN , 1);
}
void Turn_On_Cooler(){
    GPIO_SetPortPinState(PORT_C , COOLER_PIN , 1);
    GPIO_SetPortPinState(PORT_C , HEATER_PIN , 0); 
}
void Turn_off_Heater_Cooler(){
    GPIO_SetPortPinState(PORT_C , COOLER_PIN , 0);
    GPIO_SetPortPinState(PORT_C , HEATER_PIN , 0);
}

// ---------------- HEATING LED Section ---------------
void Blink_Heating_LED(){
    if (++Sec_blink_counter >= ONE_SEC / HUNDRED_MS)
    {
       if(GPIO_GetPortPinState(PORT_B , HEATER_LED_PIN) == 1){
          GPIO_SetPortPinState(PORT_B , HEATER_LED_PIN , 0);
       }else {
          GPIO_SetPortPinState(PORT_B , HEATER_LED_PIN , 1);
       }
        Sec_blink_counter =0;
    }
}
void Turn_On_Heating_LED(){
     GPIO_SetPortPinState(PORT_B , HEATER_LED_PIN , 1);
}
void Turn_Off_Heating_LED(){
     GPIO_SetPortPinState(PORT_B , HEATER_LED_PIN , 0);
}