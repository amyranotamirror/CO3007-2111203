/*
 * UDF_traffic_light.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_TRAFFIC_LIGHT_H_
#define INC_UDF_TRAFFIC_LIGHT_H_
/* Import library */
#include "UDF_button.h"
#include "UDF_led_indicator.h"
#include "UDF_led_segment.h"
/* Public variables declaration */

/* Public function declaration */
void init_fsm_traffic_light_system();
void fsm_traffic_light_system();


#endif /* INC_UDF_TRAFFIC_LIGHT_H_ */
