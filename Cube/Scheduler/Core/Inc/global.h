/*
 * global.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#define FLAG_ON		GPIO_PIN_RESET
#define FLAG_OFF 	GPIO_PIN_SET

// Port & Pin setup
typedef struct _GPIO_config{
	GPIO_TypeDef * port;
	uint16_t pin;
} GPIO_config;


#endif /* INC_GLOBAL_H_ */
