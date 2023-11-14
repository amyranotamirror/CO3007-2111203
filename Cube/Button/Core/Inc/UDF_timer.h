/*
 * UDF_timer.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_TIMER_H_
#define INC_UDF_TIMER_H_
/* Import library */
#include "main.h"
#include "UDF_global.h"

/* Public variables declaration */
#define NUM_TIMER 4
#define INTERRUPT_DURATION_MS 10		// Internal interrupt
#define LED_INDICATOR_DURATION_MS 250 	// LED indicator
#define LED_SEGMENT_DURATION_MS 10		// LED segment
#define SECOND_DURATION_MS 1000			// Clock in second
#define BUTTON_DURATION_MIN 10			// Min response time
#define BUTTON_DURATION_MAX 50			// Max response time

typedef struct{
	int limit;
	int counter;
	int flag;
}timer;
timer timers[NUM_TIMER];
/* Public function declaration */
void init_timer();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_UDF_TIMER_H_ */
