/*
 * f_uart.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#include "f_uart.h"
#include "f_fsm.h" // TEST
uint8_t rxFlag = 0;
uint8_t parserByte = 0;
char str[16];
void  HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		 HAL_UART_Receive_IT(&huart2, &parserByte, 1);
		 uint8_t temp = parserByte;
		 HAL_UART_Transmit(&huart2, &temp, sizeof(temp), 10);
		 rxFlag = 1;
	}
}

void uartSendReponse(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC:%04d#\r\n", ADC_value), UART_TIMEOUT);
}

void testSendRequest(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Request\r\n"), UART_TIMEOUT);
}

void testSendACK(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Exit\r\n"), UART_TIMEOUT);
}

void testResend(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Re-send\r\n"), UART_TIMEOUT);
}

void testBufferOvf(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Buffer ovf\r\n"), UART_TIMEOUT);
}
void testResetCmd(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Reset CMD\r\n"), UART_TIMEOUT);
}
void testStartCmd(void){
	HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "Begin CMD\r\n"), UART_TIMEOUT);
}


