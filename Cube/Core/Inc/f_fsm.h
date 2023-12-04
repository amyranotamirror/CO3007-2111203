/*
 * f_fsm.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */

#ifndef INC_F_FSM_H_
#define INC_F_FSM_H_

#include "f_uart.h"
#include "f_adc.h"
#define PARSER_BUFFER_SIZE 		8
// UART flag
#define FLAG_NONE				0
#define FLAG_REQUEST_ADC		1
#define	FLAG_EXIT_REQUEST_ADC	2
#define MATCHED					0

enum PARSER_STATE  {PARSER_IDLE = 0,
					PARSER_READING};
enum UART_STATE		{UART_WAIT_FOR_COMMAND = 0,
					UART_WAIT_FOR_ACK};
extern enum PARSER_STATE PARSER_FSM;
extern enum UART_STATE UART_FSM;
extern uint8_t uartFlag;
extern char parserBuffer[PARSER_BUFFER_SIZE];

void fsmUARTCommunication();
void fsmCommandParser();

void parserIdle();
void parserReading();
void uartWaitForCommand();
void uartWaitForAck();

#endif /* INC_F_FSM_H_ */
