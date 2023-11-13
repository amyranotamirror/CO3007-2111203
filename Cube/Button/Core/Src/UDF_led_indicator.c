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
GPIO_PinState TURN_OFF = GPIO_PIN_SET;
GPIO_PinState TURN_ON = GPIO_PIN_RESET;

/* Private function  */
void reset_led_indicator(){
	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t color = 0; color < NUM_COLOR; color++){
			HAL_GPIO_WritePin(ledIndicatorArray[side][color].port, ledIndicatorArray[side][color].pin, TURN_OFF);
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

	reset_led_indicator();
}
void display_led_indicator(TRAFFIC_LIGHT_SIDE trafficSide, TRAFFIC_LIGHT_COLOR trafficColor){
	/* At any time and at each side, only a single led can be ON.*/
	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t color = 0; color < NUM_COLOR; color++){
			if(side == trafficSide && color == trafficColor){
				HAL_GPIO_WritePin(ledIndicatorArray[side][color].port, ledIndicatorArray[side][color].pin, TURN_ON);
				continue;
			}
			HAL_GPIO_WritePin(ledIndicatorArray[side][color].port, ledIndicatorArray[side][color].pin, TURN_OFF);
		}
	}
}
