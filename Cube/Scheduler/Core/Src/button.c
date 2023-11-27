/*
 * button.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */

#include <button.h>

// Private variables / define / macros
#define NO_BUTTONS			1
#define NO_SAMPLE			3
#define BUTTON_IS_PRESSED 	GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 	GPIO_PIN_SET

typedef struct _Button{
	GPIO_config connection; // Port & Pin
	GPIO_PinState debounceBuffer[NO_SAMPLE];
	uint32_t debounceCursor;

	GPIO_PinState resultState;
	uint32_t counterForLongPress;
	uint8_t flagForLongPress;
	uint8_t flagToRespond;
} Button;
Button buttonArray[NO_BUTTONS];

uint8_t acceptButtonData(Button* this){
	// Read & Store sample data
	this->debounceBuffer[this->debounceCursor] = HAL_GPIO_ReadPin(this->connection.port, this->connection.pin);

	// Compare current sample with earlier samples
	uint8_t result = 1;
	for(uint32_t sample = 0; sample != NO_SAMPLE; sample++){
		if(this->debounceBuffer[sample] != this->debounceBuffer[(sample - 1) % NO_SAMPLE]){
			result = 0; // Refuse sample as result
			break;
		}
	}

	return result;
}

// Pubic function ---------------------------------------
void initButton(){
	// Setup pin/port for buttons
	buttonArray[0].connection = (GPIO_config){BUTTON_INPUT_GPIO_Port,
											   BUTTON_INPUT_Pin};
	// Initialize button status
	for(uint32_t index = 0; index < NO_BUTTONS; index++){
		Button *this = buttonArray[index];
		// Reset debouncing buffer
		for(uint32_t sample = 0; sample < NO_SAMPLE; sample++)
			this->debounceBuffer[sample] = BUTTON_IS_RELEASED;
		this->debounceCursor = 0;
		// Reset state / flag
		this->resultState = BUTTON_IS_RELEASED;
		this->counterForLongPress = 0;
		this->flagForLongPress = FLAG_OFF;
		this->flagToRespond = FLAG_OFF;
	}
}

void readButton(){
	for(uint32_t index = 0; index < NO_BUTTONS; index++){
		Button *this = &buttonArray[index];
		if(acceptButtonData(this)){ // Respond to accepted data
			// Save result after debounced
			this->resultState = this->debounceBuffer[this->debounceCursor];
			switch(this->resultState){
			case BUTTON_IS_PRESSED:
				// First press: Detect & Respond
				if(this->counterForLongPress == 0 &&
						this->flagForLongPress == FLAG_OFF){
					this->flagToRespond = FLAG_ON;	// Respond
				}
				// Long press until auto-increase
				else if(this->counterForLongPress >= (TIMER_BUTTON_LONG_PRESS_MS / DEFAULT_TIMER_MS)){
					this->flagForLongPress = FLAG_ON; 	// Change to auto-increase state
					this->flagToRespond = FLAG_ON; 		// Respond
					this->counterForLongPress = 0; 		// Reset counter for auto-increase
				}
				this->counterForLongPress += 1;
				break;
			case BUTTON_IS_RELEASED:
				this->counterForLongPress = 0;
				this->flagForLongPress = FLAG_OFF;
				break;
			}
		}
		// Next debounce sample
		this->debounceCursor = (this->debounceCursor + 1) % NO_SAMPLE;
	}
}

uint8_t isButtonPressed(uint16_t ID){
	return buttonArray[ID].resultState == BUTTON_IS_PRESSED;
}

uint8_t isButtonLongPressed(uint16_t ID){
	if(buttonArray[ID].flagForLongPress == FLAG_ON){
		buttonArray[ID].flagForLongPress = FLAG_OFF;// Reset flag
		return 1;
	}
	return 0;// Get state
}
uint8_t isButtonRequest(uint16_t ID){
	if(buttonArray[ID].flagToRespond == FLAG_ON){
		buttonArray[ID].flagToRespond = FLAG_OFF;
		return 1;
	}
	return 0;
}
