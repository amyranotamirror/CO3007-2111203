/*
 * scheduler.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_


#include "global.h"
#include "timer.h"
#include "button.h"


typedef struct _SchedulerTask{
	void (*pTask)(void); 	// Pointer to the task
	uint32_t period; 		// Interval between subsequent runs
	uint32_t delay; 		// Time remain before executing next task
} SchedulerTask;

#define MAX_SCHEDULE_TASK 	40
#define NO_TASK_ID			7
SchedulerTask taskArray[MAX_SCHEDULE_TASK];


/* Public function declaration */
void SCH_Init_Task();
void SCH_Update_Task();
uint16_t SCH_Add_Task(void (* pFunction) () ,
			 	 unsigned int delay,
				 unsigned int period);
void SCH_Delete_Task(uint16_t taskID);
void SCH_Dispatch_Task();
void SCH_Go_To_Sleep();

/* Task function */
void blinkLED500();
void blinkLED1000();
void blinkLED1500();
void blinkLED2000();
void blinkLED2500();
void blinkLEDoneshot();
void blinkLEDButton();
void printTime();
void printMessage(const char *msg);
#endif /* INC_SCHEDULER_H_ */
