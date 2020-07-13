#ifndef SCH_H
#define SCH_H

#include <xc.h>
#include "main.h"
// ------ Public data type declarations ----------------------------
// Store in DATA area, if possible, for rapid access
// Total memory per task is 7 bytes
typedef void (*PTask)(void);
typedef struct sTask
{
    // Pointer to the task (must be a 'void (void)' function)
      PTask pTask;
    // Delay (ticks) until the function will (next) be run
    // - see SCH_Add_Task() for further details
    tWord Delay;
    // Interval (ticks) between subsequent runs.
    // - see SCH_Add_Task() for further details
    tWord Period;
    // Incremented (by scheduler) when task is due to execute
    tByte RunMe;
} sTask;
// ------ Public function prototypes -------------------------------
// Core scheduler functions
void SCH_Dispatch_Tasks(void);
tByte SCH_Add_Task(PTask, const tWord, const tWord);
tByte SCH_Delete_Task(const tByte);
void SCH_Report_Status(void);
void SCH_Go_To_Sleep();
void SCH_Init_T1(void);
void SCH_Start(void);
// ------ Public constants -----------------------------------------
// The maximum number of tasks required at any one time
// during the execution of the program
//
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS (3)
#endif
/*------------------------------------------------------------------*-
---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/