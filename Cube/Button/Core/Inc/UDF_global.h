/*
 * UDF_global.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_GLOBAL_H_
#define INC_UDF_GLOBAL_H_
/* Import library */
#include "main.h"
#include "stdbool.h"

/* Public define */
#define NUM_SIDE 2
#define NUM_DIGIT 2
#define NUM_COLOR 3
#define TURN_OFF GPIO_PIN_SET
#define TURN_ON GPIO_PIN_RESET

/* Public variables declaration */
typedef struct _GPIO_config{
	GPIO_TypeDef* port;
	uint16_t pin;
} GPIO_config;

typedef enum {IS_PRESSED = 0, IS_RELEASED, IS_LONG_PRESSED} BUTTON_STATE ;
typedef enum {NORMAL = 0, MODIFY_RED, MODIFY_GREEN, MODIFY_AMBER} MODE;
typedef enum {RED = 0, GREEN, AMBER} TRAFFIC_LIGHT_COLOR;
typedef enum {SIDE_A = 0, SIDE_B} TRAFFIC_LIGHT_SIDE;
typedef enum {LEFT = 0, RIGHT} LED_SEG_DIGIT;
typedef enum {TIMER_BUTTON, TIMER_LED_INDICATOR, TIMER_LED_SEGMENT, TIMER_SECOND};
/* Public function declaration */


#endif /* INC_UDF_GLOBAL_H_ */
