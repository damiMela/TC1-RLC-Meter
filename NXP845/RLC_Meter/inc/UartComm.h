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

#define UART0 				USART0_PERIPHERAL
#define UART_CMD_INIT_CHAR  '$'
#define UART_CMD_END_CHAR   '@'
#define UART_CMD_LEN		5

bool UartComm_available();
bool UartComm_cmdDetected();
void UartComm_readCmd(char* cmd);
bool UartComm_readValue(uint16_t *result);
uint16_t UartComm_parseFreq(char *cmd);

#endif /* UARTCOMM_H_ */
