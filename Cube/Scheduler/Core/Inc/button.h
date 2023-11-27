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

void initButton();
void readButton();
uint8_t isButtonPressed(uint16_t ID);
uint8_t isButtonLongPressed(uint16_t ID);
uint8_t isButtonRequest(uint16_t ID);

#endif /* INC_BUTTON_H_ */
