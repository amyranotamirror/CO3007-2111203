/*
 * global.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#define FLAG_ON		GPIO_PIN_RESET
#define FLAG_OFF 	GPIO_PIN_SET

// Port & Pin setup
typedef struct _GPIO_config{
	GPIO_TypeDef * port;
	uint16_t pin;
} GPIO_config;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;

#endif /* INC_GLOBAL_H_ */
