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

#define SINUS_LENGTH 	256//2

static const uint16_t SinusOutputData[SINUS_LENGTH] = {
		512,524,537,549,562,574,587,599,612,624,636,649,661,
		673,685,696,708,720,731,743,754,765,776,786,797,807,
		818,828,837,847,856,866,875,883,892,900,908,916,924,
		931,938,945,952,958,964,970,975,981,985,990,994,998,
		1002,1006,1009,1012,1014,1016,1018,1020,1021,1022,1023,
		1023,1023,1023,1023,1022,1021,1019,1017,1015,1013,1010,
		1007,1004,1000,996,992,988,983,978,973,967,961,955,948,
		942,935,928,920,912,904,896,888,879,870,861,852,842,832,
		823,812,802,792,781,770,759,748,737,725,714,702,691,679,
		667,655,642,630,618,606,593,581,568,556,543,530,518,505,
		493,480,467,455,442,430,417,405,393,381,368,356,344,332,
		321,309,298,286,275,264,253,242,231,221,211,200,191,181,
		171,162,153,144,135,127,119,111,103,95,88,81,75,68,62,56,
		50,45,40,35,31,27,23,19,16,13,10,8,6,4,2,1,0,0,0,0,0,1,2,
		3,5,7,9,11,14,17,21,25,29,33,38,42,48,53,59,65,71,78,85,92,
		99,107,115,123,131,140,148,157,167,176,186,195,205,216,226,
		237,247,258,269,280,292,303,315,327,338,350,362,374,387,399,
		411,424,436,449,461,474,486,499,511
};

//static const uint16_t SinusOutputData[SINUS_LENGTH] = {1023,0};

void sine_generator_init(void)
{
	POWER_DisablePD(kPDRUNCFG_PD_DAC0);
}


void sine_generator_send(uint32_t value)
{
	DAC_SetBufferValue(DAC0, value);
}

void sine_generator_freq(uint32_t value) //value 30:1MHz 300:100kHz 3000:10kHz  30000:1kHz
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



