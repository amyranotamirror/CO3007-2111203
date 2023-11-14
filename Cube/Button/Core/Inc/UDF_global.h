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
#define NUM_BUTTON 3
#define NUM_MODE 4
#define TURN_OFF GPIO_PIN_SET
#define TURN_ON GPIO_PIN_RESET

/* Public variables declaration */
typedef struct _GPIO_config{
	GPIO_TypeDef* port;
	uint16_t pin;
} GPIO_config;

typedef enum {NORMAL = 0, MODIFY_RED, MODIFY_AMBER, MODIFY_GREEN} MODE;
typedef enum {SELECT_MODE, MODIFY_VALUE, SELECT_VALUE} BUTTON_PURPOSE;
typedef enum {RED = 0, AMBER, GREEN} TRAFFIC_LIGHT_COLOR;
typedef enum {SIDE_A = 0, SIDE_B} TRAFFIC_LIGHT_SIDE;
typedef enum {LEFT = 0, RIGHT} LED_SEG_DIGIT;
typedef enum {TIMER_BUTTON = 0, TIMER_LED_INDICATOR, TIMER_LED_SEGMENT, TIMER_SECOND} TIMING;
/* Public function declaration */


#endif /* INC_UDF_GLOBAL_H_ */
