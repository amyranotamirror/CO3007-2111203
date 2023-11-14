/*
 * UDF_led_indicator.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_led_indicator.h"
/* Private variables declaration */
GPIO_config ledIndicatorPhysical[NUM_SIDE][NUM_COLOR];
uint8_t toggleState = TURN_OFF;

/* Private function  */
void turn_all_led_indicator_off(){
	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t color = 0; color < NUM_COLOR; color++){
			HAL_GPIO_WritePin(ledIndicatorPhysical[side][color].port, ledIndicatorPhysical[side][color].pin, TURN_OFF);
		}
	}
}
void turn_all_led_indicator_on(){
	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t color = 0; color < NUM_COLOR; color++){
			HAL_GPIO_WritePin(ledIndicatorPhysical[side][color].port, ledIndicatorPhysical[side][color].pin, TURN_ON);
		}
	}
}

/* Public function  */
void init_led_indicator(){
	ledIndicatorPhysical[SIDE_A][RED] = (GPIO_config){RED_0_GPIO_Port, RED_0_Pin};
	ledIndicatorPhysical[SIDE_A][GREEN] = (GPIO_config){GREEN_0_GPIO_Port, GREEN_0_Pin};
	ledIndicatorPhysical[SIDE_A][AMBER] = (GPIO_config){AMBER_0_GPIO_Port, AMBER_0_Pin};

	ledIndicatorPhysical[SIDE_B][RED] = (GPIO_config){RED_1_GPIO_Port, RED_1_Pin};
	ledIndicatorPhysical[SIDE_B][GREEN] = (GPIO_config){GREEN_1_GPIO_Port, GREEN_1_Pin};
	ledIndicatorPhysical[SIDE_B][AMBER] = (GPIO_config){AMBER_1_GPIO_Port, AMBER_1_Pin};

	turn_all_led_indicator_off();
}
void display_led_indicator(TRAFFIC_LIGHT_SIDE trafficSide, TRAFFIC_LIGHT_COLOR trafficColor){
	/* At any time and at each side, only a single led can be ON.*/
	for(uint16_t color = 0; color < NUM_COLOR; color++){
		if(color == trafficColor){
			HAL_GPIO_WritePin(ledIndicatorPhysical[trafficSide][color].port, ledIndicatorPhysical[trafficSide][color].pin, TURN_ON);
			continue;
		}
		HAL_GPIO_WritePin(ledIndicatorPhysical[trafficSide][color].port, ledIndicatorPhysical[trafficSide][color].pin, TURN_OFF);
	}
}
void blink_all_led(){
	if(toggleState == TURN_OFF){
		turn_all_led_indicator_off();
		toggleState = TURN_ON;
	}
	else{
		turn_all_led_indicator_on();
		toggleState = TURN_OFF;
	}
}
