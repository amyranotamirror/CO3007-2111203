/*
 * UDF_led_segment.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_led_segment.h"

/* Private define */
typedef struct _ledSegment{
	GPIO_config ledSegmentPhysical;
	int numberToDisplay;
} ledSegment;
int SEGMENT_HEX[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0xFF};

/* Private variables declaration */
static int enabledLedSegmentSide = SIDE_A;
static int enabledLedSegmentDigit = LEFT;
ledSegment ledSegments[NUM_SIDE][NUM_DIGIT];

/* Public function  */
void init_led_segment(){
	ledSegments[SIDE_A][LEFT].ledSegmentPhysical = (GPIO_config){EN0_LEFT_GPIO_Port, EN0_LEFT_Pin};
	ledSegments[SIDE_A][RIGHT].ledSegmentPhysical = (GPIO_config){EN0_RIGHT_GPIO_Port, EN0_RIGHT_Pin};
	ledSegments[SIDE_B][LEFT].ledSegmentPhysical = (GPIO_config){EN1_LEFT_GPIO_Port, EN1_LEFT_Pin};
	ledSegments[SIDE_B][RIGHT].ledSegmentPhysical = (GPIO_config){EN1_RIGHT_GPIO_Port, EN1_RIGHT_Pin};

	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t digit = 0; digit < NUM_DIGIT; digit++){
			HAL_GPIO_WritePin((ledSegments[side][digit].ledSegmentPhysical).port, (ledSegments[side][digit].ledSegmentPhysical).pin, TURN_OFF);
			ledSegments[side][digit].numberToDisplay = 0;
		}
	}

}

void modify_led_segment_buffer(TRAFFIC_LIGHT_SIDE trafficSide, uint16_t number){
	ledSegments[trafficSide][LEFT].numberToDisplay = number / 10;
	ledSegments[trafficSide][RIGHT].numberToDisplay = number % 10;
}

void display_led_segment(){
	if(timers[TIMER_LED_SEGMENT].flag == TURN_ON){
		// Write data to LED segment
		GPIOB->ODR = (GPIOB->ODR & (0xFF << 8))
				| (SEGMENT_HEX[ledSegments[enabledLedSegmentSide][enabledLedSegmentDigit].numberToDisplay]);

		// Enable correct LED segment
		for(uint16_t side = 0; side < NUM_SIDE; side++){
			for(uint16_t digit = 0; digit < NUM_DIGIT; digit++){
				if(side == enabledLedSegmentSide && digit == enabledLedSegmentDigit)
					HAL_GPIO_WritePin((ledSegments[side][digit].ledSegmentPhysical).port, (ledSegments[side][digit].ledSegmentPhysical).pin, TURN_ON);
				else HAL_GPIO_WritePin((ledSegments[side][digit].ledSegmentPhysical).port, (ledSegments[side][digit].ledSegmentPhysical).pin, TURN_OFF);
			}
		}

		// Toggle to another LEDs
		if(enabledLedSegmentDigit == RIGHT)
			enabledLedSegmentSide = (enabledLedSegmentSide + 1) % NUM_SIDE;
		enabledLedSegmentDigit = (enabledLedSegmentDigit + 1) % NUM_DIGIT;
		timers[TIMER_LED_SEGMENT].flag = TURN_OFF;
	}
}
