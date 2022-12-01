/*
 * UartComm.C
 *
 *  Created on: 25 nov. 2022
 *      Author: Damian - PC
 */

#include  "UartComm.h"
#include  "globalTimer.h"

char rcv_cmd[UART_CMD_LEN+1];

bool UartComm_available(){
	return kUSART_RxReady & USART_GetStatusFlags(UART0);
}

bool UartComm_cmdDetected(){
	bool result = false;
	if(UartComm_available()){
		USART_ReadBlocking(UART0, (uint8_t*)rcv_cmd, (UART_CMD_LEN+1)*sizeof(char));
	}

	if(rcv_cmd[0] == UART_CMD_INIT_CHAR) result = true;
	rcv_cmd[0] = 0;
	return result;
}

void UartComm_readCmd(char cmd[UART_CMD_LEN]){
	strcpy(cmd, rcv_cmd+1);
}

bool UartComm_readValue(uint16_t *result){
	char buff[10] = {0};
	uint8_t index = 0;

	if(!UartComm_available()) return false;

	timer_setValue(UART_TIMEOUT_TIMER, 3000);
	while((buff[index] != UART_CMD_END_CHAR)){
		if(timer_getStatus(UART_TIMEOUT_TIMER)) return false;

		buff[index]=USART_ReadByte(UART0);
 		index++;
		timer_reset(UART_TIMEOUT_TIMER);
	}
	buff[index] = 0;
	//*result = UartComm_parseFreq(buff);

	return true;
}

uint16_t UartComm_parseFreq(char *cmd){
	uint16_t result = -1;

	if(strstr(cmd, "K") != NULL){
			*(cmd+strlen(cmd)) = 0;
			result = atol(cmd+1)*1000;
	}
	else{
		result = atol(cmd+1);
	}
	return result;
}

void UartComm_write(char *txt, uint8_t len){
	USART_WriteBlocking(UART0, txt, len);
}

