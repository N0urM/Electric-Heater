#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

// ------ Public constants -----------------------------------------
#define RETURN_NORMAL 0
#define RETURN_ERROR  1
#define _XTAL_FREQ    8000000

#define HEATER_PIN               5
#define COOLER_PIN               2
#define HEATING_SENSOR_PIN       2
#define HEATING_SENSOR_CHANNEL   2
#define HEATER_LED_PIN           6

// Periods are defined depending on Scheduler frequencty of main task
#define ONE_SEC         50
#define FIVE_SEC        250
#define HUNDRED_MS      5


typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;

// Error codes (SCH))
//----------------------------------------------------------------------
#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)
#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK (0xAA)
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER (0xAA)
#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START (0xA0)
#define ERROR_SCH_LOST_SLAVE (0x80)
#define ERROR_I2C_WRITE_BYTE_AT24C64 (11)
#define ERROR_I2C_READ_BYTE_AT24C64 (12)
#define ERROR_I2C_WRITE_BYTE (13)
#define ERROR_I2C_READ_BYTE (14)
#define ERROR_USART_TI (21)
#define ERROR_USART_WRITE_CHAR (22)

#endif