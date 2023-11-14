/*
 * UDF_traffic_light.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_traffic_light.h"

/* Private variables declaration */
#define RESPONSE_NEEDED 1
#define NO_RESPONSE_NEEDED 0
typedef struct _trafficLightSystem{
	MODE mode;								// Current system mode
	uint16_t countDownLimit[NUM_COLOR];		// Limit for each color
	uint16_t countDownTimer[NUM_SIDE]; 		// Counter for each side
	TRAFFIC_LIGHT_COLOR colors[NUM_SIDE];	// Color for each side
} trafficLightSystem;
trafficLightSystem system;
uint16_t test[2] = {30, 20};
/* Private function  */
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
		 }
	 }

	 return result;
}

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
					system.colors[side] = AMBER;
					break;
				case AMBER:
					system.colors[side] = GREEN;
					break;
				case GREEN:
					system.colors[side] = RED;
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
	if(timers[TIMER_SECOND].flag == TURN_ON){
		modify_led_segment_buffer(SIDE_A, test[0]);
		modify_led_segment_buffer(SIDE_B, test[1]);
		test[0]--;
		test[1]--;
		timers[TIMER_SECOND].flag = TURN_OFF;
	}
//	switch(system.mode){
//	// Traffic light running normally
//	case NORMAL:
//		if(timers[TIMER_SECOND].flag == TURN_ON){
//			// Count down each second
//			system.countDownTimer[SIDE_A]--;
//			system.countDownTimer[SIDE_B]--;
//			// Display the count down number
//			modify_led_segment_buffer(SIDE_A, system.countDownTimer[SIDE_A]);
//			modify_led_segment_buffer(SIDE_B, system.countDownTimer[SIDE_B]);
//		}
//		break;
//	// Other cases: Modify mode
//	modify_led_segment_buffer(SIDE_A, system.mode);
//	case MODIFY_RED:
//		modify_led_segment_buffer(SIDE_B, system.countDownLimit[RED]);
//		break;
//	case MODIFY_AMBER:
//		modify_led_segment_buffer(SIDE_B, system.countDownLimit[AMBER]);
//		break;
//	case MODIFY_GREEN:
//		modify_led_segment_buffer(SIDE_B, system.countDownLimit[GREEN]);
//		break;
//	}
//	// Reset timer flag of second tracker
//	timers[TIMER_SECOND].flag = TURN_OFF;
}

/* Public function  */
void init_fsm_traffic_light_system(){
	// Initiate sub-modules
	init_timer();
//	init_led_indicator();
	init_led_segment();
//	init_button();

//	// Set initial values for traffic light
//	system.mode = NORMAL;
//	system.colors[SIDE_A] = RED;
//	system.colors[SIDE_B] = GREEN;
//	system.countDownLimit[RED] = 5;
//	system.countDownLimit[AMBER] = 2;
//	system.countDownLimit[GREEN] = 3;
//	for(uint8_t side = 0; side < NUM_SIDE; side++){
//		system.countDownTimer[side] = system.countDownLimit[system.colors[side]];
//	}
}

void fsm_traffic_light_system(){
	/* Output display: led indicator, led segment*/
//	fsm_led_indicator();
	fsm_led_segment();

//	/* Read & Process buttons*/
//	button_reading();
//	uint8_t button_response[NUM_BUTTON];
//	// Catch button trigger
//	for(uint16_t index; index < NUM_BUTTON; index++)
//		button_response[index] = respond_to_button(index);
//
//	/* Temporary value for modify */
//	uint16_t tempValue = 0;
//
//	/* Finite state machine: Modes */
//	switch(system.mode){
//	case NORMAL:
//		// Mode switching
//		if(button_response[SELECT_MODE] == RESPONSE_NEEDED)
//			system.mode = MODIFY_RED;
//		break;
//	case MODIFY_RED:
//		// Mode switching
//		if(button_response[SELECT_MODE] == RESPONSE_NEEDED)
//			system.mode = MODIFY_AMBER;
//		// Modify value
//		tempValue = system.countDownLimit[RED];
//
//		break;
//	case MODIFY_AMBER:
//		// Mode switching
//		if(button_response[SELECT_MODE] == RESPONSE_NEEDED)
//			system.mode = MODIFY_GREEN;
//		// Modify value
//		tempValue = system.countDownLimit[AMBER];
//		break;
//	case MODIFY_GREEN:
//		// Mode switching
//		if(button_response[SELECT_MODE] == RESPONSE_NEEDED)
//			system.mode = NORMAL;
//		// Modify value
//		tempValue = system.countDownLimit[GREEN];
//		break;
//	}
}
