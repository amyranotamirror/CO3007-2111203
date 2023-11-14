/*
 * UDF_button.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Amyra Nguyen
 */


/* Import library */
#include "UDF_button.h"
/* Private variables declaration */
int buttonSampleLimit = 1;
int buttonSampleBuffer[100];

/* Private function  */
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
	buttonSampleLimit = calculate_button_sample_limit();
}
