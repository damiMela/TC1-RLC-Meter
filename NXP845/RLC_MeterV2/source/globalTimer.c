/*
 * Delay.c
 *
 *  Created on: 18 nov. 2022
 *      Author: Damian - PC
 */
#include <globalTimer.h>

volatile uint16_t timerCounter[4] = {0};
uint16_t timerValue[4] = {0};
uint8_t timerFlags = 0;
uint16_t delayTime = 0;

void SysTick_Handler(void)
{
	delayTime++;
	for(int i = 0; i < 3; i++){
		timerCounter[i]++;
		if(timerCounter[i] >= timerValue[i]){
			timerFlags |= (1 << i);
			timerCounter[i] = 0;
		}
	}
}

void timer_setValue(timer_n timer, uint16_t val){
	timer_reset(timer);
	timerValue[timer] = val;
}

void timer_reset(timer_n timer){
	timerCounter[timer] = 0;
}

bool timer_getStatus(timer_n timer){
	if(timerFlags & (1<<timer)){
		timerFlags &= ~(1 << timer);
		return true;
	}
	return false;
}

void delayMs(uint16_t val){
	delayTime = 0;
	while(delayTime < val);
}
