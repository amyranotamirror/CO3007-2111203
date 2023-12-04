/*
 * f_adc.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#include "f_adc.h"

int ADC_value = 0;

void ADCRead(void){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	ADC_value = HAL_ADC_GetValue(&hadc1);
}
