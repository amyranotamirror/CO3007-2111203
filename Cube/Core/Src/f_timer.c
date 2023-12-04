/*
 * f_timer.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */


#include "f_timer.h"

uint32_t resendCounter = 0;
uint8_t timeoutFlag = TIMER_IDLE;
uint32_t systemTickCounter = 0;
uint8_t systemTickFlag = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == htim2.Instance){
		if(timeoutFlag == TIMER_IDLE){
			timerReset();
		} else if(timeoutFlag == TIMER_COUNTING){
			resendCounter++;
			if(resendCounter >= RESEND_TIME_OUT_DURATION){
				timeoutFlag = TIMER_EXCEED;
				resendCounter = 0;
			}
		}
		if(systemTickCounter >= TICK_DURATION){
			systemTickFlag = 1;
			systemTickCounter = 0;
		} else{
			systemTickCounter++;
		}
	}
}

void timerReset(){
	resendCounter = 0;
}
