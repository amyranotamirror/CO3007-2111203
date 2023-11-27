/*
 * timer.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */


#include "timer.h"

/* Public function  */
void init_timer(){
	// Set counter limit to raise a flag
	timerArray[LED_500].limit = TIMER_LED_500_MS / DEFAULT_TIMER_MS;
	timerArray[LED_1000].limit = TIMER_LED_1000_MS / DEFAULT_TIMER_MS;
	timerArray[LED_1500].limit = TIMER_LED_1500_MS / DEFAULT_TIMER_MS;
	timerArray[LED_2000].limit = TIMER_LED_2000_MS / DEFAULT_TIMER_MS;
	timerArray[LED_2500].limit = TIMER_LED_2500_MS / DEFAULT_TIMER_MS;
	timerArray[LED_BUTTON].limit = TIMER_BUTTON_LONG_PRESS_MS / DEFAULT_TIMER_MS;

	// Reset counter and flag to default value
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		timerArray[timer].counter = timerArray[timer].limit;
		timerArray[timer].flag = 0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		timerArray[timer].counter--;
		if(timerArray[timer].counter <= 0){
			timerArray[timer].flag = TURN_ON; 	// Raise the flag
			timerArray[timer].counter = timerArray[timer].limit;	// Reset counter
		}
	}
}
