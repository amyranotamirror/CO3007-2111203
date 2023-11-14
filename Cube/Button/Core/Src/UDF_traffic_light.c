/*
 * UDF_traffic_light.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_traffic_light.h"

/* Private variables declaration */
typedef struct _trafficLightSystem{
	MODE mode;								// Current system mode
	uint16_t countDownLimit[NUM_COLOR];		// Limit for each color
	uint16_t countDownTimer[NUM_SIDE]; 		// Counter for each side
	TRAFFIC_LIGHT_COLOR colors[NUM_SIDE];	// Color for each side
} trafficLightSystem;
trafficLightSystem system;

// Response to button actions
#define RESPONSE_NEEDED 1
#define NO_RESPONSE_NEEDED 0
#define DEFAULT_MODIFY_VALUE 100
BUTTON_PURPOSE button_to_response = NONE;
uint16_t modifyValue = DEFAULT_MODIFY_VALUE;

/* Private function  */
void fsm_led_indicator(){
	if(system.mode == NORMAL){
		// Display traffic color as normal
		display_led_indicator(SIDE_A, system.colors[SIDE_A]);
		display_led_indicator(SIDE_B, system.colors[SIDE_B]);

		// Change color state each side
		for(uint8_t side = 0; side < NUM_SIDE; side++){
			if(system.countDownTimer[side] <= 0){
				switch(system.colors[side]){
				case RED:
					system.colors[side] = GREEN;
					system.countDownTimer[side] = system.countDownLimit[GREEN];
					break;
				case AMBER:
					system.colors[side] = RED;
					system.countDownTimer[side] = system.countDownLimit[RED];
					break;
				case GREEN:
					system.colors[side] = AMBER;
					system.countDownTimer[side] = system.countDownLimit[AMBER];
				}
			}
		}
	}
	else{// Blink LEDs in other modes
		if(timers[TIMER_LED_INDICATOR].flag == TURN_ON){
			blink_all_led();
			timers[TIMER_LED_INDICATOR].flag = TURN_OFF;
		}
	}
}

void fsm_led_segment(){
	display_led_segment();
	switch(system.mode){
	// Traffic light running normally
	case NORMAL:
		if(timers[TIMER_SECOND].flag == TURN_ON){
			// Count down each second
			system.countDownTimer[SIDE_A]--;
			system.countDownTimer[SIDE_B]--;
			// Display the count down number
			modify_led_segment_buffer(SIDE_A, system.countDownTimer[SIDE_A]);
			modify_led_segment_buffer(SIDE_B, system.countDownTimer[SIDE_B]);
		}
		break;
	// Other cases: Modify mode
	case MODIFY_RED:
		modify_led_segment_buffer(SIDE_A, system.mode);
		modify_led_segment_buffer(SIDE_B, system.countDownLimit[RED]);
		break;
	case MODIFY_AMBER:
		modify_led_segment_buffer(SIDE_A, system.mode);
		modify_led_segment_buffer(SIDE_B, system.countDownLimit[AMBER]);
		break;
	case MODIFY_GREEN:
		modify_led_segment_buffer(SIDE_A, system.mode);
		modify_led_segment_buffer(SIDE_B, system.countDownLimit[GREEN]);
		break;
	}
	// Reset timer flag of second tracker
	timers[TIMER_SECOND].flag = TURN_OFF;
}

uint8_t respond_to_button(BUTTON_PURPOSE buttonIndex){
	uint8_t result = NO_RESPONSE_NEEDED;
	// Response to certain actions
	if(is_button_response_needed(buttonIndex)){
		 finish_to_respond(buttonIndex); // Reset after responds
		 switch(buttonIndex){
			 // Response to: Single press only
			 case SELECT_MODE:
			 case SELECT_VALUE:
				 if(!is_button_long_pressed(buttonIndex))
					 result = RESPONSE_NEEDED;
				 break;
			 // Response to: Single/Long press
			 case MODIFY_VALUE:
				 result = RESPONSE_NEEDED;
				 break;
			 default: break;
		 }
	 }
	 return result;
}

void fsm_button(){
	/* Read & Process buttons*/
	if(timers[TIMER_BUTTON].flag == TURN_ON){
		button_reading();
		timers[TIMER_BUTTON].flag = TURN_OFF;
	}

	// Catch button trigger: Prioritized (BTN1 > BTN2 > BTN3)
	for(int index = NUM_BUTTON - 1; index >= 0; index--){
		if(respond_to_button(index) == RESPONSE_NEEDED){
			button_to_response = index;
		}
	}

}

/* Public function  */
void init_fsm_traffic_light_system(){
	// Initiate sub-modules
	init_timer();
	init_led_indicator();
	init_led_segment();
	init_button();

	// Set initial values for traffic light
	system.mode = NORMAL;
	system.colors[SIDE_A] = RED;
	system.colors[SIDE_B] = GREEN;
	system.countDownLimit[RED] = 5;
	system.countDownLimit[AMBER] = 2;
	system.countDownLimit[GREEN] = 3;
	for(uint8_t side = 0; side < NUM_SIDE; side++){
		system.countDownTimer[side] = system.countDownLimit[system.colors[side]];
	}
}

void fsm_traffic_light_system(){
	/* Output display: led indicator, led segment*/
	fsm_led_indicator();
	fsm_led_segment();
	fsm_button();

	/* Finite state machine: Button to mode */
	switch(button_to_response){
	case SELECT_MODE:
		// Go to next mode, reset modify value
		system.mode = (system.mode + 1) % NUM_MODE;
		modifyValue = DEFAULT_MODIFY_VALUE;
		if(system.mode == NORMAL){
			// Display LEDs segment: Traffic count down
			modify_led_segment_buffer(SIDE_A, system.countDownTimer[SIDE_A]);
			modify_led_segment_buffer(SIDE_B, system.countDownTimer[SIDE_B]);
		}
		else{
			// Display LEDs segment: Mode, Modify value
			modifyValue = system.countDownLimit[system.mode - 1];
			modify_led_segment_buffer(SIDE_A, system.mode);
			modify_led_segment_buffer(SIDE_B, modifyValue);
		}
		break;
	case MODIFY_VALUE:
		if(system.mode != NORMAL){
			// Increase value
			modifyValue = (modifyValue + 1) % DEFAULT_MODIFY_VALUE;
			modify_led_segment_buffer(SIDE_B, modifyValue);
		}
		break;
	case SELECT_VALUE:
		if(system.mode != NORMAL){
			// Save modified value
			system.countDownLimit[system.mode - 1] = modifyValue;
		}
		break;
	default: break;
	}
	button_to_response = NONE;// Reset response trigger
}
