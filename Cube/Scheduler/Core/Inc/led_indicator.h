/*
 * led_indicator.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_LED_INDICATOR_H_
#define INC_LED_INDICATOR_H_

#include "global.h"
#include "timer.h"

/* Public define / macros */
#define NO_LED			7
#define LED_ON			GPIO_PIN_RESET
#define LED_OFF			GPIO_PIN_SET
typedef enum {LED_500 = 0,
			  LED_1000,
			  LED_1500,
			  LED_2000,
			  LED_2500,
			  LED_ONESHOT,
			  LED_BUTTON } LED_INDICATOR;

/* Public function declaration */
void initLEDIndicator();
void writeLEDState(LED_INDICATOR led, GPIO_PinState state);
void toggleLEDState(LED_INDICATOR led);

#endif /* INC_LED_INDICATOR_H_ */
