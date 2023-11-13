/*
 * UDF_led_segment.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_LED_SEGMENT_H_
#define INC_UDF_LED_SEGMENT_H_
/* Import library */
#include "UDF_global.h"
/* Public variables declaration */

/* Public function declaration */
void init_led_segment();
void modify_led_segment_buffer(TRAFFIC_LIGHT_SIDE trafficSide, uint16_t number);


#endif /* INC_UDF_LED_SEGMENT_H_ */
