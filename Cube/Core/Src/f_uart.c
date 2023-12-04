/*
 * f_uart.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#include "f_uart.h"
uint8_t rxFlag = 0;
uint8_t parserByte = 0;

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		 HAL_UART_Receive_IT(&huart2, &parserByte, 1);\
		 uint8_t temp = parserByte;
		 HAL_UART_Transmit(huart, &temp, sizeof(temp), 10);
		 rxFlag = 1;
	}
}

void uartSendReponse(void){
	char str[16];
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC:%04d#\r\n", ADC_value), UART_TIMEOUT);
}

void testSendRequest(void){
	char str[32];
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Request\r\n"), UART_TIMEOUT);
}

void testSendACK(void){
	char str[32];
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Exit\r\n"), UART_TIMEOUT);
}

void testResend(void){
	char str[32];
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Re-send\r\n"), UART_TIMEOUT);
}



