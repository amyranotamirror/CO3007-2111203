/*
 * UDF_timer.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_timer.h"
/* Private variables declaration */

/* Private function  */
int calculate_button_sample_rate(){
	// Internal interrupt duration is: >10ms and <50ms
	if(INTERRUPT_DURATION_MS > BUTTON_DURATION_MIN && INTERRUPT_DURATION_MS < BUTTON_DURATION_MAX)
		return 1;
	// Internal interrupt duration is: <10ms
	return (BUTTON_DURATION_MIN / INTERRUPT_DURATION_MS) + 1;
}

/* Public function  */
void init_timer(){
	// Reset counter and flag to default value
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		timers[timer].counter = 0;
		timers[timer].flag = 0;
	}
	// Set counter limit to raise a flag
	timers[TIMER_BUTTON].limit = calculate_button_sample_rate();
	timers[TIMER_LED_INDICATOR].limit = LED_INDICATOR_DURATION_MS / INTERRUPT_DURATION_MS;
	timers[TIMER_LED_SEGMENT].limit = LED_SEGMENT_DURATION_MS / INTERRUPT_DURATION_MS;
	timers[TIMER_LED_SEGMENT].limit = SECOND_DURATION_MS / INTERRUPT_DURATION_MS;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	for(uint16_t timer = 0; timer < NUM_TIMER; timer++){
		if(timers[timer].counter >= timers[timer].limit){
			timers[timer].flag = 1; 	// Raise the flag
			timers[timer].counter = 0;	// Reset counter
		}
	}
}
