/*
 * f_uart.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#include "main.h"
#include "f_uart.h"

#define UART_TIMEOUT 100
extern UART_HandleTypeDef huart2;

void uartTransmit(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC:%04lu#\r\n", trafficRedDuration / 1000), 100);
}
