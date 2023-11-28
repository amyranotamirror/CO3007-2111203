/*
 * scheduler.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */


#include "scheduler.h"
/* Private function */
uint16_t currentTaskID = 0;
void SCH_Init_Task(){
	for(uint16_t index = 0; index < MAX_SCHEDULE_TASK && taskArray[index].pTask; index++){
		SCH_Delete_Task(index);
	}
	// Init components
	initTimer();
	initButton();
}

void SCH_Update_Task(){
	for(uint16_t index = 0; index < MAX_SCHEDULE_TASK; index++){
		if(taskArray[index].delay > 0){
			taskArray[index].delay -= 1;
		} else{
			taskArray[index].flag = 1;
		}
	}
}

uint16_t SCH_Add_Task(void (* pFunction) () ,
			 	 unsigned int delay,
				 unsigned int period){
	// Array is full
	if(currentTaskID >= MAX_SCHEDULE_TASK)
		return MAX_SCHEDULE_TASK;
	// Add task to the last index
	taskArray[currentTaskID].pTask = pFunction;
	taskArray[currentTaskID].delay = delay;
	taskArray[currentTaskID].period = period;
	taskArray[currentTaskID].flag = 0;
	currentTaskID++; // Move to next task
	return currentTaskID;
}

void SCH_Delete_Task(uint16_t taskID){
	if(taskArray[taskID].pTask != 0 &&
			taskID >= 0 && taskID < MAX_SCHEDULE_TASK){
		return;// No task to delete
	}
	// Shift task forward
	for(uint16_t index = taskID; index < currentTaskID - 1; index++){
		taskArray[index].pTask = taskArray[index + 1].pTask;
		taskArray[index].delay = taskArray[index + 1].delay;
		taskArray[index].period = taskArray[index + 1].period;
		taskArray[index].flag = taskArray[index + 1].flag;
	}
	// Delete task at the back
	taskArray[currentTaskID - 1].pTask = 0x0000;
	taskArray[currentTaskID - 1].delay = 0;
	taskArray[currentTaskID - 1].period = 0;
	taskArray[currentTaskID - 1].flag = 0;
	currentTaskID--; // Reduce number of tasks
}

void SCH_Dispatch_Task(){
	for(uint16_t index = 0; index < currentTaskID; index++){
		if(taskArray[index].flag == 1){
			// Execute task & Clear flag
			(*taskArray[index].pTask)();
			taskArray[index].flag = 0;
			taskArray[index].delay = taskArray[index].period;
			// Delete one-shot task
			if(taskArray[index].period == 0){
				SCH_Delete_Task(index);
			}
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
