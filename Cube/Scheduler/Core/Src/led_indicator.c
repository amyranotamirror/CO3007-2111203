/*
 * led_indicator.c
 *
 *  Created on: 26 thg 11, 2023
 *      Author: Amyra Nguyen
 */


#include "led_indicator.h"

/* Private define / macros */
typedef struct _LEDIndicator{
	GPIO_config *connection;
	GPIO_PinState state;
} LEDIndicator;
LEDIndicator ledArray[NO_LED];

/* Public function declaration */
void initLEDIndicator(){
	// Setup port / pin
	ledArray[LED_500].connection = (GPIO_config){LED_500_GPIO_Port, LED_500_Pin};
	ledArray[LED_1000].connection = (GPIO_config){LED_1000_GPIO_Port, LED_1000_Pin};
	ledArray[LED_1500].connection = (GPIO_config){LED_1500_GPIO_Port, LED_1500_Pin};
	ledArray[LED_2000].connection = (GPIO_config){LED_2000_GPIO_Port, LED_2000_Pin};
	ledArray[LED_2500].connection = (GPIO_config){LED_2500_GPIO_Port, LED_2500_Pin};
	ledArray[LED_ONESHOT].connection = (GPIO_config){LED_ONESHOT_GPIO_Port, LED_ONESHOT_Pin};
	ledArray[LED_BUTTON].connection = (GPIO_config){LED_BUTTON_GPIO_Port, LED_BUTTON_Pin};

	// Turn all LEDs off
	for(uint16_t index = 0; index < NO_LED; index++){
		writeLEDState(ledArray[index], LED_OFF);
	}
	// Turn LED oneshot on
	writeLEDState(ledArray[LED_ONESHOT], LED_ON);
}

void writeLEDState(LED_INDICATOR led, GPIO_PinState state){
	ledArray[led].state = state; // Update state
	HAL_GPIO_WritePin(ledArray[led].connection->port, ledArray[led].connection->pin, state);
}

void toggleLEDState(LED_INDICATOR led){
	ledArray[led].state = !ledArray[led].state; // Update state
	HAL_GPIO_TogglePin(ledArray[led].connection->port, ledArray[led].connection->port);
}
