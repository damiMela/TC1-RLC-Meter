/*
 * UartComm.C
 *
 *  Created on: 25 nov. 2022
 *      Author: Damian - PC
 */

#include  "UartComm.h"
#include  "globalTimer.h"

uint8_t uartCommand;

bool UartComm_available(){
	return kUSART_RxReady & USART_GetStatusFlags(UART0);
}

bool UartComm_cmdDetected(){
	uint8_t uartPacket;
	if(UartComm_available()){
		USART_ReadBlocking(UART0, &uartPacket, sizeof(char));

		switch(uartPacket){
			case START_CMD_CHAR: 	uartCommand = START_CMD; break;
			default: return false;
		}
		return true;
	}
	return false;
}

uint8_t UartComm_readCmd(){
	return uartCommand;
}

void UartComm_write(uint8_t *txt, uint8_t len){
	USART_WriteBlocking(UART0, txt, len);
}

