/*
 * timer.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */


#include "timer.h"

/* Public function  */
void initTimer(){
	HAL_TIM_Base_Start_IT(&htim2);
}


void watchDog(){

}
