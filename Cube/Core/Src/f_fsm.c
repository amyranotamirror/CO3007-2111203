/*
 * f_fsm.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Amyra Nguyen
 */


#include "f_fsm.h"

char parserBuffer[PARSER_BUFFER_SIZE];
uint8_t parserIndex = 0;
uint8_t uartFlag = FLAG_NONE;

enum PARSER_STATE PARSER_FSM = PARSER_IDLE;
enum UART_STATE UART_FSM = UART_WAIT_FOR_COMMAND;

void fsmCommandParser(){
	if(rxFlag  == 1){
		switch(PARSER_FSM){
		case PARSER_IDLE:
			parserIdle();
			break;
		case PARSER_READING:
			parserReading();
			break;
		}
		rxFlag = 0;
	}
}

void fsmUARTCommunication(){
	switch(UART_FSM){
	case UART_WAIT_FOR_COMMAND:
		uartWaitForCommand();
		break;
	case UART_WAIT_FOR_ACK:
		uartWaitForCommand();
		uartWaitForAck();
		break;
	}
}

void parserIdle(){
	// Clear buffer
	parserIndex = 0;
	parserBuffer[parserIndex] = '\0';
	// Start reading if a command begin
	if(parserByte == '!'){
		parserBuffer[parserIndex++] = parserByte;
		PARSER_FSM = PARSER_READING;
	}
}

void parserReading(){
	if(parserByte == '!'){// Read as new command
		parserIndex = 0;
		parserBuffer[parserIndex++] = parserByte;
	}
	else if(parserByte == '\b'){//Delete character
		parserBuffer[parserIndex--] = '\0';
		if(parserIndex <= 0){
			PARSER_FSM = PARSER_IDLE;
		}
	}
	else if(parserByte == '\r'){// Process input
		if(strcmp(parserBuffer, "!OK#") == MATCHED){
			uartFlag = FLAG_EXIT_REQUEST_ADC;
			testSendRequest();
		}
		if(strcmp(parserBuffer, "!RST#") == MATCHED){
			uartFlag = FLAG_REQUEST_ADC;
			testSendRequest();
		}
		PARSER_FSM = PARSER_IDLE;
	}
	else{// Store data
		parserBuffer[parserIndex++] = parserByte;
	}

	// Check for buffer overflow
	if(parserIndex >= PARSER_BUFFER_SIZE){
		PARSER_FSM = PARSER_IDLE;
	}
}



void uartWaitForCommand(){
	if(uartFlag == FLAG_REQUEST_ADC){//REQUESTED
		uartFlag = FLAG_NONE;
		timerReset();
		timeoutFlag = TIMER_COUNTING;
		ADCRead();
		uartSendReponse();
		testSendRequest();
		UART_FSM = UART_WAIT_FOR_ACK;
	}
}

void uartWaitForAck(){
	if(uartFlag == FLAG_EXIT_REQUEST_ADC){//ACKED
		uartFlag = FLAG_NONE;
		timeoutFlag = TIMER_IDLE;
		UART_FSM = UART_WAIT_FOR_COMMAND;
		testSendACK();
	} else if(timeoutFlag == TIMER_EXCEED){
		timerReset();
		timeoutFlag = TIMER_COUNTING;
		uartSendReponse();
		testResend();
	}
}
