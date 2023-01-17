/*
 * delay.h
 *
 *  Created on: 18 nov. 2022
 *      Author: Damian - PC
 */

#ifndef HEADERS_GLOBALTIMERS_H_
#define HEADERS_GLOBALTIMERS_H_

#include "board.h"

typedef enum _timer_n{
	LED_TIMER,
	UART_TIMEOUT_TIMER,
	ADC_TIMEOUT_TIMER,
	DAC_TIMER,
	TIMER5,
	TIMER6,
	TIMER7,
	TIMER8
} timer_n;



void SysTick_Handler(void);
void timer_setValue(timer_n timer, uint16_t val);
bool timer_getStatus(timer_n timer);
void timer_reset(timer_n timer);
void delayMs(uint16_t val);

#endif /* HEADERS_GLOBALTIMERS_H_ */
