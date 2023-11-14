/*
 * UDF_button.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_button.h"

/* Private define */
#define BUTTON_IS_PRESSED TURN_ON
#define BUTTON_IS_RELEASED TURN_OFF
typedef struct _button{
	GPIO_config* physical;
	GPIO_PinState sampleBuffer[100];
	GPIO_PinState state;
	uint16_t counterForLongPress; // Delay before auto increase
	uint16_t flagToIncrease;	  // Allow to increase
	uint16_t flagForLongPress;	  // Delay state
} button;

/* Private variables declaration */
static int buttonSampleLimit = 1;
static int durationForAutoIncreasing = 1;
static int currentSampleIndex = 0;
// Button class
button buttons[NUM_BUTTON];

/* Private function */
int calculate_button_sample_limit(){
	/* Invalid range of timer */
	if(INTERRUPT_DURATION_MS >= 50)
		return 0;

	// Interrupt duration is: > 10ms and < 50ms
	if(INTERRUPT_DURATION_MS > BUTTON_DURATION_MIN && INTERRUPT_DURATION_MS < BUTTON_DURATION_MAX)
		return BUTTON_DURATION_MAX / INTERRUPT_DURATION_MS;

	// Interrupt duration is: < 10ms
	int sampleLimit = (BUTTON_DURATION_MIN / INTERRUPT_DURATION_MS) + 1;
	while(sampleLimit * INTERRUPT_DURATION_MS < BUTTON_DURATION_MAX)
		sampleLimit += timers[TIMER_BUTTON].limit;
	return sampleLimit / timers[TIMER_BUTTON].limit;
}

/* Public function  */
void init_button(){
	// Calculate value for button sampling, auto increase
	buttonSampleLimit = calculate_button_sample_limit();

	// Set physical port and pin
	buttons[0].physical = (GPIO_config*){BUTTON_1_GPIO_Port, BUTTON_1_Pin};
	buttons[1].physical = (GPIO_config*){BUTTON_2_GPIO_Port, BUTTON_2_Pin};
	buttons[2].physical = (GPIO_config*){BUTTON_3_GPIO_Port, BUTTON_3_Pin};
	// Set button initial state
	for(uint16_t index = 0; index < NUM_BUTTON; index++){
		buttons[index].state = BUTTON_IS_RELEASED;
		buttons[index].counterForLongPress = 0;
		buttons[index].flagForLongPress = TURN_OFF;
		buttons[index].flagToIncrease = TURN_OFF;
		// Reset sample buffer
		for(uint16_t sample = 0; sample < buttonSampleLimit; sample++){
			buttons[index].sampleBuffer[sample] = TURN_OFF;
		}
	}
}

void button_reading(){
	/* Trigger: Button sampling with timer interrupt, flag raised */

	for(uint16_t index = 0; index < NUM_BUTTON; index++){
		// Sampling button input and shifting buffer
		buttons[index].sampleBuffer[(currentSampleIndex - 1) % buttonSampleLimit]
			= buttons[index].sampleBuffer[currentSampleIndex];
		buttons[index].sampleBuffer[currentSampleIndex]
			= HAL_GPIO_ReadPin(buttons[index].physical->port, buttons[index].physical->pin);

		// Enough samples: compare first and current sample
		if((buttons[index].sampleBuffer[currentSampleIndex] == buttons[index].sampleBuffer[0])
			&& (currentSampleIndex == buttonSampleLimit - 1)){
			// Response to input: Update state
			buttons[index].state = buttons[index].sampleBuffer[currentSampleIndex];

			if(buttons[index].state == BUTTON_IS_PRESSED){
				// If a button is first pressed, increased once
				if(buttons[index].flagForLongPress == TURN_OFF
						&& buttons[index].counterForLongPress == 0){
					buttons[index].flagToIncrease = TURN_ON; // Increase by one
				}

				// If a button is pressed, we start counting
				if(buttons[index].counterForLongPress < durationForAutoIncreasing){
					buttons[index].counterForLongPress++;
				}
				else{
					buttons[index].flagToIncrease = TURN_ON; // Increase
					buttons[index].flagForLongPress = TURN_ON;
					buttons[index].counterForLongPress = 1; // Reset, end cycle
				}
			}
			else{
				buttons[index].counterForLongPress = 0; // Reset, button release
				buttons[index].flagForLongPress = TURN_OFF;
			}
		}

	}
	timers[TIMER_BUTTON].flag = TURN_OFF; // Reset flag
	currentSampleIndex = (currentSampleIndex + 1) % buttonSampleLimit;
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
	return (buttons[index].flagToIncrease == TURN_ON);
}

void finish_to_respond(uint16_t index){
	buttons[index].flagToIncrease = TURN_OFF;
}

