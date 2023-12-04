/*
 * f_adc.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_F_ADC_H_
#define INC_F_ADC_H_
#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern int ADC_value;

void ADCRead(void);

#endif /* INC_F_ADC_H_ */
