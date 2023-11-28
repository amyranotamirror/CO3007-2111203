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
#define BUTTON_IS_PRESSED 	GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 	GPIO_PIN_SET

void initButton();
void readButton();
uint8_t isButtonPressed(uint16_t ID);
uint8_t isButtonLongPressed(uint16_t ID);
uint8_t isButtonRequest(uint16_t ID);

#endif /* INC_BUTTON_H_ */
