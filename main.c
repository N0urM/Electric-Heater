#include <xc.h>
#include "main.h"
#include "SCH.h"
#include "Electrical_Heater.h"


void main() { 

  // Set up Electrical Heater  
  EH_Init();
  // Set up the scheduler
  SCH_Init_T1();
  // Add Tasks
   SCH_Add_Task(EH_Update , 0, 20);
   SCH_Add_Task(Seg7_Update , 0, 2);
   SCH_Add_Task(Heating_Elements_Update , 0 , 100);
  // Start the scheduler
  SCH_Start();

  while(1)
  {
     SCH_Dispatch_Tasks();
  }
     
}