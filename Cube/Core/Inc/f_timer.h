/*
 * f_timer.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_F_TIMER_H_
#define INC_F_TIMER_H_

#include "main.h"
#define RESEND_TIME_OUT_DURATION	300
#define TICK_DURATION				100
#define TIMER_IDLE		0
#define TIMER_COUNTING 	1
#define TIMER_EXCEED	2

extern TIM_HandleTypeDef htim2;
extern uint8_t timeoutFlag;
extern uint8_t systemTickFlag;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void timerReset();
#endif /* INC_F_TIMER_H_ */
