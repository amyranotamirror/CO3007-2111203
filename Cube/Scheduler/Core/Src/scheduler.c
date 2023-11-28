/*
 * scheduler.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */


#include "scheduler.h"
/* Private function */
void SCH_Init_Task(){
	for(uint16_t index = 0; index < MAX_SCHEDULE_TASK && taskArray[index].pTask; index++){
		SCH_Delete_Task(index);
	}
	// Init components
	initTimer();
	initButton();
}

void SCH_Update_Task(){
	if(taskArray[0].pTask != 0 && taskArray[0].delay > 0)
		taskArray[0].delay -= 1;
}

uint16_t SCH_Add_Task(void (* pFunction) () ,
			 	 unsigned int delay,
				 unsigned int period){
	// Check if array is full
	if(taskArray[MAX_SCHEDULE_TASK - 1].pTask != 0) return MAX_SCHEDULE_TASK;

	uint32_t currentDelay = delay;
	uint16_t currentID = 0;

	// Find position to insert task
	while(taskArray[currentID].pTask != 0
			&& currentID < MAX_SCHEDULE_TASK
			&& currentDelay >= taskArray[currentID].delay){
		currentDelay -= taskArray[currentID].delay;
		currentID++;
	}

	// Shift array backward if current position is occupied
	if(taskArray[currentID].pTask != 0){
		for(uint16_t index = MAX_SCHEDULE_TASK - 1; index > currentID; index--){
			if(taskArray[index - 1].pTask != 0){
				// Shift data to the back
				taskArray[index].pTask = taskArray[index - 1].pTask;
				taskArray[index].period = taskArray[index - 1].period;
				// Modify delay relative to interval of the previous task
				taskArray[index].delay = taskArray[index - 1].delay - currentDelay;
			}
		}
	}

	// Insert task to appropriate position
	taskArray[currentID].pTask = pFunction;
	taskArray[currentID].period = period;
	taskArray[currentID].delay = currentDelay;
	return currentID; // Return position
}

void SCH_Delete_Task(uint16_t taskID){
	if(taskArray[taskID].pTask == 0)
		return; // No task to delete

	// Shift array forward if there's tasks at the back
	for(; taskID < MAX_SCHEDULE_TASK - 1 && taskArray[taskID + 1].pTask != 0; taskID++){
		// Shift data to the front
		taskArray[taskID].pTask = taskArray[taskID + 1].pTask;
		taskArray[taskID].period = taskArray[taskID + 1].period;
		taskArray[taskID].delay = taskArray[taskID + 1].delay;
	}

	// Delete task data at the tail
	taskArray[taskID].pTask = 0x0000;
	taskArray[taskID].period = 0;
	taskArray[taskID].delay = 0;
}

void SCH_Dispatch_Task(){
	if(taskArray[0].pTask == 0)
		return; // No task to dispatch
	while(taskArray[0].delay <= 0 && taskArray[0].pTask != 0){
		(*taskArray[0].pTask)();

		// Temporary task
		SchedulerTask tempTask;
		tempTask.pTask = taskArray[0].pTask;
		tempTask.period = taskArray[0].period;
		SCH_Delete_Task(0);		// Delete task at the front
		if(tempTask.period != 0){// Add recurring task
			SCH_Add_Task(tempTask.pTask, tempTask.period, tempTask.period);
		}
	}
}


/* Task function */
void blinkLED500(){
	HAL_GPIO_TogglePin(LED_500_GPIO_Port, LED_500_Pin);
//	printMessage("LED 0.5s");
}

void blinkLED1000(){
	HAL_GPIO_TogglePin(LED_1000_GPIO_Port, LED_1000_Pin);
//	printMessage("LED 1s");
}

void blinkLED1500(){
	HAL_GPIO_TogglePin(LED_1500_GPIO_Port, LED_1500_Pin);
//	printMessage("LED 1.5s");
}

void blinkLED2000(){
	HAL_GPIO_TogglePin(LED_2000_GPIO_Port, LED_2000_Pin);
//	printMessage("LED 2s");
}

void blinkLED2500(){
	HAL_GPIO_TogglePin(LED_2500_GPIO_Port, LED_2500_Pin);
//	printMessage("LED 2.5s");
}

void blinkLEDoneshot(){
	HAL_GPIO_WritePin(LED_ONESHOT_GPIO_Port, LED_ONESHOT_Pin, GPIO_PIN_SET);
//	printMessage("LED one shot");
}

void blinkLEDButton(){
	readButton();
	if(isButtonRequest(0)){
		HAL_GPIO_TogglePin(LED_BUTTON_GPIO_Port, LED_BUTTON_Pin);
//		printMessage("Toggle buttons");
	}
}

void printTime(){
	printMessage("\nHello");
}

void printMessage(const char *msg){
	char data[100];
//	uint8_t len = sprintf(data, "%s: %lu\r", msg, systemTimer);
	HAL_UART_Transmit(&huart1, (uint8_t*)data, 1, 500);
}
