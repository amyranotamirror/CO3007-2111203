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
	GPIO_TypeDef *ledSegmentPhysical;
	int isEnable;
	int numberToDisplay;
} ledSegment;

/* Private variables declaration */
int LED_SEG_HEX = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0xFF};
ledSegment ledSegments[NUM_SIDE][NUM_DIGIT];

/* Private function */
void toggle_led_segment(){

}
/* Public function  */
void init_led_segment(){
	ledSegments[SIDE_A][LEFT] = (GPIO_config){};
	ledSegments[SIDE_A][RIGHT] = (GPIO_config){};
	ledSegments[SIDE_B][LEFT] = (GPIO_config){};
}

void modify_led_segment_buffer(TRAFFIC_LIGHT_SIDE trafficSide, uint16_t number);
