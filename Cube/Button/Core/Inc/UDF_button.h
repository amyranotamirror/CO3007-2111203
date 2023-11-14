/*
 * UDF_button.h
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_UDF_BUTTON_H_
#define INC_UDF_BUTTON_H_

/* Import library */
#include "UDF_global.h"
#include "UDF_timer.h"

/* Public variables declaration */

/* Public function declaration */
void init_button();
void button_reading();
unsigned char is_button_pressed(uint16_t index);
unsigned char is_button_long_pressed(uint16_t index);
unsigned char is_button_response_needed(uint16_t index);
void finish_to_respond(uint16_t index);

#endif /* INC_UDF_BUTTON_H_ */
