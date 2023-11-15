/*
 * UDF_timer.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

/* Import library */
#include "UDF_timer.h"

/* Public function  */
void init_timer(){
	// Set counter limit to raise a flag
	timers[TIMER_BUTTON].limit = BUTTON_DURATION_MIN / INTERRUPT_DURATION_MS;
	timers[TIMER_LED_INDICATOR].limit = LED_INDICATOR_DURATION_MS / INTERRUPT_DURATION_MS;
	timers[TIMER_LED_SEGMENT].limit = LED_SEGMENT_DURATION_MS / INTERRUPT_DURATION_MS;
	timers[TIMER_SECOND].limit = SECOND_DURATION_MS / INTERRUPT_DURATION_MS;

	// Reset counter and flag to default value
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		timers[timer].counter = timers[timer].limit;
		timers[timer].flag = 0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		timers[timer].counter--;
		if(timers[timer].counter <= 0){
			timers[timer].flag = TURN_ON; 	// Raise the flag
			timers[timer].counter = timers[timer].limit;	// Reset counter
		}
	}
}
