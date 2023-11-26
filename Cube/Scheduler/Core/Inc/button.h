/*
 * button.h
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"
#include "timer.h"

typedef enum {IS_RELEASE,
			  IS_PRESSED,
			  IS_LONG_PRESSED} BUTTON_STATE ;

void initButton();
void readButton();
uint16_t isButtonPressed(uint16_t ID);
uint16_t isButtonLongPressed(uint16_t ID);

#endif /* INC_BUTTON_H_ */
