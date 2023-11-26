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

	BUTTON_STATE resultState;
	uint32_t counterForLongPress;
	uint8_t flagForLongPress;
} Button;
Button buttonArray[NO_BUTTONS];

// Private functions
void resetButton(Button* this){
	this->resultState = IS_RELEASE;
	this->counterForLongPress = 0;
	this->flagForLongPress = 0;
}

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
		// Reset debouncing variables once
		for(uint32_t sample = 0; sample < NO_SAMPLE; sample++)
			buttonArray[index].debounceBuffer[sample] = BUTTON_IS_RELEASED;
		buttonArray[index].debounceCursor = 0;
		resetButton(&buttonArray[index]);
	}
}

void readButton(){
	for(uint32_t index = 0; index < NO_BUTTONS; index++){
		Button *this = &buttonArray[index];
		if(acceptButtonData(this)){ // Respond to accepted data
			// Pressed button: Single or Long press
			if(this->debounceBuffer[this->debounceCursor] == BUTTON_IS_PRESSED){
				if(this->counterForLongPress <= (TIMER_BUTTON_LONG_PRESS_MS / DEFAULT_TIMER_MS)){
					this->counterForLongPress++; // Counting when pressed
				} else{
					this->flagForLongPress = 1; // Raise flag after time, since pressed
				}
			}
			// Release button: Clear long press
			else{
				resetButton(this);
			}
		}
		// Next debounce sample
		this->debounceCursor = (this->debounceCursor + 1) % NO_SAMPLE;
	}
}

uint16_t isButtonPressed(uint16_t ID){
	uint16_t result = 0;
	if(buttonArray[ID].resultState == IS_PRESSED){
		buttonArray[ID].counterForLongPress != 0;
		result = 1;// Get state
	}
	return result;
}

uint16_t isButtonLongPressed(uint16_t ID){
	uint16_t result = 0;
	if(buttonArray[ID].resultState == IS_LONG_PRESSED){
		buttonArray[ID].flagForLongPress = 0;// Reset flag
		result = 1;
	}
	return result;// Get state
}
