/*
 * sine_generator.c
 *
 *  Created on: 5 sep. 2022
 *      Author: juan
 */

#include "sine_generator.h"
#include "fsl_dac.h"
#include "fsl_power.h"
#include "peripherals.h"

#define SINUS_LENGTH 	50

/* MATLAB script
  	%1Hz 250kHz
	counter_ticks = 60000;
	fro = 30e6;
	time_tick = counter_ticks / fro;
	puntos = 50;
	periodo = puntos *time_tick;
	frec = 1/periodo;

	%con 2 ticks --> 300kHz
	%con 25 ticks --> 24kHz
	%con 250 ticks --> 2.4kHz
	%con 2500 ticks --> 240Hz
	%con 25000 ticks --> 24Hz
	%con 60000 ticks --> 10Hz

	counter_ticks = 120;
	fro = 30e6; %30MHz
	time_tick = counter_ticks / fro;
	frec = 2500;
	periodo = 1/frec;
	puntos = periodo / (2*time_tick);
	t = linspace(0,2*pi,puntos);
	y = sin(t)+1;
	y = fix(y * 1024/2);
	csvwrite('sin.txt',y);

*/
static const uint16_t SinusOutputData[SINUS_LENGTH] = {
		512,577,641,704,763,818,868,912,949,980,1002,1017,
		1023,1021,1011,992,965,931,891,843,791,734,673,609,
		544,479,414,350,289,232,180,132,92,58,31,12,2,0,6,
		21,43,74,111,155,205,260,319,382,446,511
};

//static const uint16_t SinusOutputData[SINUS_LENGTH] = {1023,0};

void sine_generator_init(void)
{
	sine_generator_freq(60000);
	POWER_DisablePD(kPDRUNCFG_PD_DAC0);

}


void sine_generator_send(uint32_t value)
{
	DAC_SetBufferValue(DAC0, value);
}

void sine_generator_freq(uint32_t value)
{
	DAC_SetCounterValue(DAC0, value);
}


/* DAC0_IRQn interrupt handler */
void DAC0_IRQHandler(void) {
 	static uint8_t index = 0;
	sine_generator_send(SinusOutputData[index]);
	index++;
	if (index == SINUS_LENGTH)
	{
		index = 0;
	}

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}



