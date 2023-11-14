/*
 * UDF_led_indicator.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_LED_INDICATOR_H_
#define INC_UDF_LED_INDICATOR_H_
/* Import library */
#include "UDF_global.h"
#include "UDF_timer.h"
/* Public variables declaration */

/* Public function declaration */
void init_led_indicator();
void display_led_indicator(TRAFFIC_LIGHT_SIDE trafficSide, TRAFFIC_LIGHT_COLOR trafficColor);
void blink_all_led();



#endif /* INC_UDF_LED_INDICATOR_H_ */
