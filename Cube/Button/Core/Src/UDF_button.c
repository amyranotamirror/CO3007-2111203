/*
 * UDF_button.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_button.h"

/* Private define */
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET
#define DELAY_BEFORE_LONG_PRESS_MS (BUTTON_DURATION_MAX * 10)
#define DURATION_FOR_AUTO_INCREASE_MS (NUM_DEBOUNCE * INTERRUPT_DURATION_MS)

typedef struct _button{
	GPIO_config physical;
	GPIO_PinState state;
	int currentSampleIndex;
	int counterForLongPress; // Delay before auto increase
	uint8_t flagToResponse;	  	 // Allow to increase
	uint8_t flagForLongPress;	 // Delay state
} button;

/* Private variables declaration */
static GPIO_PinState debounceBuffer[NUM_DEBOUNCE][NUM_BUTTON];
button buttons[NUM_BUTTON];

/* Public function  */
void init_button(){
	// Calculate value for button sampling, auto increase

	// Set physical port and pin
	buttons[0].physical = (GPIO_config){BUTTON_1_GPIO_Port, BUTTON_1_Pin};
	buttons[1].physical = (GPIO_config){BUTTON_2_GPIO_Port, BUTTON_2_Pin};
	buttons[2].physical = (GPIO_config){BUTTON_3_GPIO_Port, BUTTON_3_Pin};

	// Set button initial state
	for(uint16_t index = 0; index < NUM_BUTTON; index++){
		buttons[index].state = BUTTON_IS_RELEASED;
		buttons[index].counterForLongPress = 0;
		buttons[index].flagForLongPress = TURN_OFF;
		buttons[index].flagToResponse = TURN_OFF;
	}
}

void button_reading(){
	/* Trigger: Button sampling with timer interrupt, flag raised */
	for(int index = 0; index < NUM_BUTTON; index++){
		// Shift buffer & Read pin
		debounceBuffer[2][index] = debounceBuffer[1][index];
		debounceBuffer[1][index] = debounceBuffer[0][index];
		debounceBuffer[0][index] = HAL_GPIO_ReadPin(
				buttons[index].physical.port, buttons[index].physical.pin);

		// Filter 3 most recent data
		if ((debounceBuffer[0][index] == debounceBuffer[1][index])
				&& (debounceBuffer[0][index] == debounceBuffer[2][index])) {

			// Detect a press/release
			if(buttons[index].state != debounceBuffer[0][index]){
				buttons[index].state = debounceBuffer[0][index];

				// Detect press: Delay & Response first time
				if(buttons[index].state == BUTTON_IS_PRESSED){
					// Count down for delay before long press
					buttons[index].counterForLongPress
					= DELAY_BEFORE_LONG_PRESS_MS / INTERRUPT_DURATION_MS;
					buttons[index].flagToResponse = TURN_ON;
				}

				// Detect release: Reset state
				if(buttons[index].state == BUTTON_IS_RELEASED){
					buttons[index].counterForLongPress = 0;
					buttons[index].flagForLongPress = TURN_OFF;
				}
			}
			// Simply sampling data
			else{
				if(buttons[index].state == BUTTON_IS_PRESSED){
					buttons[index].counterForLongPress--;
					//Start auto-increase at certain rate
					if(buttons[index].counterForLongPress <= 0){
						buttons[index].flagForLongPress = TURN_ON;
						buttons[index].flagToResponse = TURN_ON;
						buttons[index].counterForLongPress
						= DURATION_FOR_AUTO_INCREASE_MS / INTERRUPT_DURATION_MS;
					}
				}
			}
		}
	}
}

unsigned char is_button_pressed(uint16_t index){
	if(index >= NUM_BUTTON) return 0;
	return (buttons[index].state == BUTTON_IS_PRESSED);
}

unsigned char is_button_long_pressed(uint16_t index){
	if(index >= NUM_BUTTON) return 0;
	return (buttons[index].flagForLongPress == TURN_ON);
}

unsigned char is_button_response_needed(uint16_t index){
	if(index >= NUM_BUTTON) return 0;
	return (buttons[index].flagToResponse == TURN_ON);
}

void finish_to_respond(uint16_t index){
	buttons[index].flagToResponse = TURN_OFF;
}

