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
	GPIO_config *ledSegmentPhysical;
	int isEnable;
	int numberToDisplay;
} ledSegment;
int LED_SEG_HEX = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0xFF};

/* Private variables declaration */
int NUM_LED_SEGMENT = 4;
static int currentEnabledLedSegment = 0;
ledSegment ledSegments[NUM_SIDE][NUM_DIGIT];

/* Private function */

/* Public function  */
void init_led_segment(){
	ledSegments[SIDE_A][LEFT].ledSegmentPhysical = (GPIO_config*){EN0_LEFT_GPIO_Port, EN0_LEFT_Pin};
	ledSegments[SIDE_A][RIGHT].ledSegmentPhysical = (GPIO_config*){EN0_RIGHT_GPIO_Port, EN0_RIGHT_Pin};
	ledSegments[SIDE_B][LEFT].ledSegmentPhysical = (GPIO_config*){EN1_LEFT_GPIO_Port, EN1_LEFT_Pin};
	ledSegments[SIDE_B][RIGHT].ledSegmentPhysical = (GPIO_config*){EN1_RIGHT_GPIO_Port, EN1_RIGHT_Pin};

	for(uint16_t side = 0; side < NUM_SIDE; side++){
		for(uint16_t color = 0; color < NUM_COLOR; color++){
			HAL_GPIO_WritePin((ledSegments[side][color].ledSegmentPhysical)->port, (ledSegments[side][color].ledSegmentPhysical)->pin, TURN_OFF);
		}
	}
}

void modify_led_segment_buffer(TRAFFIC_LIGHT_SIDE trafficSide, uint16_t number){
	ledSegments[trafficSide][LEFT].numberToDisplay = number / 10;
	ledSegments[trafficSide][RIGHT].numberToDisplay = number % 10;
}
