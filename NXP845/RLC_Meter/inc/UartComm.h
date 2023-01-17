/*
 * UartComm.h
 *
 *  Created on: 25 nov. 2022
 *      Author: Damian - PC
 */

#ifndef UARTCOMM_H_
#define UARTCOMM_H_

#include "board.h"
#include "peripherals.h"

enum{
	NO_CMD,
	START_CMD
};

#define UART0 				 USART0_PERIPHERAL
#define START_CMD_CHAR			'S'

bool UartComm_available();
bool UartComm_cmdDetected();
uint8_t UartComm_readCmd();
void UartComm_write(uint8_t *txt, uint8_t len);

#endif /* UARTCOMM_H_ */
