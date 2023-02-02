/*
 * sine_generator.c
 *
 *  Created on: 17 nov. 2022
 *      Author: Damian - PC
 */
#include <sineGenerator.h>


#include "fsl_dac.h"
#include "fsl_power.h"
#include "peripherals.h"
#include  "math.h"

volatile uint8_t dacSamples = 0;
uint8_t cylceCounter = 0;
uint16_t currentFrec;

volatile uint8_t index = 0;
static int cycleCounter = 0;
static int frec = 0;

#if SINE_RESOLUTION == 50
	static const uint16_t SinusOutputData[SINE_RESOLUTION] = {
			512,577,641,704,763,818,868,912,949,980,1002,1017,
			1023,1021,1011,992,965,931,891,843,791,734,673,609,
			544,479,414,350,289,232,180,132,92,58,31,12,2,0,6,
			21,43,74,111,155,205,260,319,382,446,511
	};

#elif SINE_RESOLUTION == 100
	static const uint16_t SinusOutputData[SINE_RESOLUTION]={
			512,544,577,609,640,671,702,732,760,788,815,840,865,
			887,909,928,946,962,977,989,1000,1009,1015,1020,1022,
			1023,1021,1018,1012,1005,995,983,970,955,937,919,898,
			876,853,828,802,774,746,717,687,656,625,593,561,528,
			496,463,431,399,368,337,307,278,250,222,196,171,148,
			126,105,87,69,54,41,29,19,12,6,3,1,2,4,9,15,24,35,47,
			62,78,96,115,137,159,184,209,236,264,292,322,353,384,
			415,447,480,512
	};
#else
	static const uint16_t SinusOutputData[5]={512,512,512,512,512};
#endif



void sineGenerator_init(void)
{
	POWER_DisablePD(kPDRUNCFG_PD_DAC0);
}

void sineGenerator_stop(){
	POWER_EnablePD(kPDRUNCFG_PD_DAC0);
	cycleCounter=0;
}

void sineGenerator_send(uint32_t value)
{
	DAC_SetBufferValue(DAC0, value);
}

void sineGenerator_freq(uint32_t value)
{
	frec = value;
	DAC_SetCounterValue(DAC0, value*30);
}

uint8_t sineGenerator_getPhase(){
	int n = index-ceil(SINE_RESOLUTION/4);
	int deg = 0;
	n = n<0 ? n+SINE_RESOLUTION : n;

	deg =((n*360)/(SINE_RESOLUTION-1));
	return deg>180 ? deg-360 : deg;
}

uint8_t sineGenerator_getCycleCount(){
	return cycleCounter;
}

void sineGenerator_resetCycleCount(){
	cycleCounter=0;
}

/* DAC0_IRQn interrupt handler */
void DAC0_IRQHandler(void) {
	int n = 0;

	if(index <(SINE_RESOLUTION-n))	sineGenerator_send(SinusOutputData[index+n]);
	else	sineGenerator_send(SinusOutputData[index-(SINE_RESOLUTION-n)]);

	index++;

	if (index == SINE_RESOLUTION){
		cycleCounter++;
		index = 0;
	}

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}
