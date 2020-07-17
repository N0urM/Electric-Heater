#include "Electrical_Heater.h"

//--------------------Private Variables------------------------------
static tByte MODE_SETTING = OFF_STATE;
static tByte set_Temp;
static tByte avg_temp = 0;
static tByte blink_sec_counter = 0;
static tByte five_sec_counter  = 0;
static tByte dis_sec_counter = 0;

// ------ Private functions prototypes ------------------------------
void On_Display();
void On_Setting(tByte set);
void Off_Display();

/* ------ Initialize Heater ----------------------------------------
 - Initialize heating elements
 - Initialize Display
 - Initialize EEPROM
 - Initialize Push_Btns
 - Read initial temp
------------------------------------------------------------------*/
void EH_Init(){
    EXT_E2PROM_Init();
    Heating_Elements_init(); 
    Seg7_Init();
    // push_btns
    PB_Init(PB_POWER , PB_RELEASED);
    PB_Init(PB_PLUS  , PB_RELEASED);
    PB_Init(PB_MINUS , PB_RELEASED);
    tByte temp_data = EXT_E2PROM_Read(BYTE_ADDRESS);
    
     if (temp_data > 75 || temp_data < 35)
     {
           EXT_E2PROM_Write(BYTE_ADDRESS , INITIAL_TEMP);    // Set initial temp
           set_Temp = INITIAL_TEMP;
     }
     else{
         set_Temp = temp_data;
     }
     
     Set_Seg7(set_Temp/10 , set_Temp%10);
}

/* ------ Heater Operator -------------------------------
 This main task running by the Scheduler
 it Splits the system into a set of states and makes use 
 of the idea of MULTI-STATE TASK to replace multiple tasks 
 with a single task that performs different activities 
 depending on the current state of the system.
 
 * It takes advantage of the fact that system may only exist 
     in one of 3 states and can NEVER take any other state:
 
 * OFF Display State: all system off 
 * On  Display State: Regular update to the Display to match 
    system readings acquired every 100 ms and displayed every 1 s
 * Setting mode State: Allows the user to update the set temp 

---------------------------------------------------------*/
void EH_Update (void){

     PB_Update();
     switch (MODE_SETTING)
     {
            case OFF_STATE:
            {
              if (PB_GetState(PB_POWER) == PB_PRE_RELEASED ) //ON/OFF btn pressed
              {
                 MODE_SETTING = ON_DISPLAY_STATE;
              }
              else 
              {
                 Off_Display();
              }
              break;
            }
            case ON_DISPLAY_STATE:
            {
              if (PB_GetState(PB_POWER) == PB_PRE_RELEASED) //ON/OFF btn pressed
              {
                 MODE_SETTING = OFF_STATE;
              }
              else if (PB_GetState(PB_PLUS) == PB_PRE_RELEASED
                       || PB_GetState(PB_MINUS) == PB_PRE_RELEASED) //UP  or DOWN btn Pressed
              {
                 MODE_SETTING = ON_SETTING_STATE;
                 blink_sec_counter = 0;
                 set_Temp = EXT_E2PROM_Read(BYTE_ADDRESS);
                 if (set_Temp > 75 || set_Temp < 35){ // EEPROM Failed 
                     set_Temp = INITIAL_TEMP;
                 }
                 On_Setting(SETTING_MODE);
              }
              else {

                    On_Display();
              }
              break;
            }
            case ON_SETTING_STATE:
            {
               if (++blink_sec_counter >= ONE_SEC){
                 set_Seg_mode(BLINK_MODE);
                 blink_sec_counter = 0;
               }
               if (PB_GetState(PB_PLUS) == PB_PRE_RELEASED )//UP BTN Pressed
               {
                 On_Setting(SETTINGP);
                 five_sec_counter = 0;
               }
               else if (PB_GetState(PB_MINUS) == PB_PRE_RELEASED ) // DOWN BTN Pressed
               {
                 On_Setting(SETTINGM);
                 five_sec_counter = 0;
               }
               else if (PB_GetState(PB_POWER) == PB_PRE_RELEASED ) //ON/OFF btn pressed
               {

                    MODE_SETTING = OFF_STATE;
                    EXT_E2PROM_Write(BYTE_ADDRESS , set_Temp);
               }
               else {
                     if(++five_sec_counter >= FIVE_SEC){
                      five_sec_counter = 0 ;
                      MODE_SETTING = ON_DISPLAY_STATE;
                      EXT_E2PROM_Write(BYTE_ADDRESS , set_Temp);
                     }
               }
               break;
            }
     }
}

/* ------ On Display -------------------------------
 FSM state : On Display
 Role: 
       - Update the 7seg to indicate current temp every 1s
       - Read sensor every 100 ms
       - Update avg temp
       - Update Heating Elements state 
---------------------------------------------------------*/
void On_Display(){
     set_heating_mode(HEATING_MODE);
     avg_temp = get_Avg_Temp();
     set_Seg_mode(UPDATE_MODE);
     if(++dis_sec_counter >= ONE_SEC)
     {
       Set_Seg7(avg_temp/10 , avg_temp%10);
       dis_sec_counter = 0;
     }
}
/* ------ On Setting -------------------------------
 FSM state : Setting mode
 Role:
       - Update 7Seg display to reflect the selected Temp
       - Update the Set Temp variable
---------------------------------------------------------*/
void On_Setting(tByte set){
    set_heating_mode(NO_HEATING_MODE);
     if (set == SETTINGP){
         set_Temp+=5 ;
         if(set_Temp > 75)
             set_Temp = 75;
     }else if (set == SETTINGM){
         set_Temp-=5 ;
         if(set_Temp < 35) 
             set_Temp = 35;
     }
     Set_Seg7(set_Temp/10 , set_Temp%10);
}

/* ------ OFF Display ------------------------------------
 FSM state : System off
 Role:
       - Turns off all system Display
         while maintaining user settings
---------------------------------------------------------*/
void Off_Display(){
     set_Seg_mode(OFF_MODE);
     set_heating_mode(NO_HEATING_MODE);
}

/*--------Getter for user setting-----------------------*/
tByte Get_Setting_Temp(){
    return set_Temp;
}
// End of File