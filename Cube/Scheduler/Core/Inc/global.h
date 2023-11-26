/*
 * global.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

// Port & Pin setup
typedef struct _GPIO_config{
	GPIO_TypeDef * port;
	uint16_t pin;
} GPIO_config;


#endif /* INC_GLOBAL_H_ */
