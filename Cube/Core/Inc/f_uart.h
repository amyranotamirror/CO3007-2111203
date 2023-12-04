/*
 * f_uart.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_F_UART_H_
#define INC_F_UART_H_

#include "main.h"
#include "f_adc.h"
#include "f_timer.h"

#define UART_TIMEOUT 			100
extern UART_HandleTypeDef huart2;
extern uint8_t rxFlag;
extern uint8_t parserByte;

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void uartSendReponse();

void testSendRequest(void);
void testSendACK(void);
void testResend(void);

#endif /* INC_F_UART_H_ */
