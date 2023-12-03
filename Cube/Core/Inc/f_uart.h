/*
 * f_uart.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_F_UART_H_
#define INC_F_UART_H_

#define UART_BUFFER_SIZE 32

typedef struct {
	char buffer[UART_BUFFER_SIZE];
} _UARTBuffer;

void UARTReceive(void);
void UARTTransmit(void);

#endif /* INC_F_UART_H_ */
