/*
 * timer.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global.h"
/* Public define / macros */
#define NO_TIMERS					7
#define DEFAULT_TIMER_MS 			100
#define TIMER_LED_500_MS			500
#define TIMER_LED_1000_MS			1000
#define TIMER_LED_1500_MS			1500
#define TIMER_LED_2000_MS			2000
#define TIMER_LED_2500_MS			2500
#define TIMER_BUTTON_LONG_PRESS_MS 	2000
#define TIMER_LED_ONESHOT_MS		1000

typedef struct{
	int limit;
	int counter;
	int flag;
} Timer;
Timer timerArray[NO_TIMERS];

/* Public function declaration */
void init_timer();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */


