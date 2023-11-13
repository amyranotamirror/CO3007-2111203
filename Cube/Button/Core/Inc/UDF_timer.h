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
#define NUM_TIMER 10
/* Public function declaration */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_UDF_TIMER_H_ */
