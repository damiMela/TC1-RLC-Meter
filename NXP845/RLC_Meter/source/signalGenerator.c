/*
 * generator.c
 *
 *  Created on: 17 nov. 2022
 *      Author: Damian - PC
 */
#include "signalGenerator.h"
#include  "math.h"

volatile uint8_t dacSamples = 0;
uint8_t cylceCounter = 0;
uint16_t currentFrec;
uint8_t currentScale = 0;


void SignalGen_setScale(uint8_t scale){
	if((scale > 100) || (scale == currentScale)) return;

	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);

	if(scale > currentScale){
		GPIO_PortSet(GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN_MASK);

		for(int i=currentScale; i<scale; i++){
			delayMs(20);
			GPIO_PortClear(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
			delayMs(20);
			GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
			scale++;
		}
	}
	else{
		GPIO_PortClear(GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN_MASK);

		for(int i=currentScale; i>scale; i--){
			delayMs(20);
			GPIO_PortClear(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
			delayMs(20);
			GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
			scale--;
		}
	}

	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
}

void SignalGen_resetScale(){
	//set potentiometer to "enable, down mode, keep value"
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN_MASK);
	GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);

	for(int i=0; i<POT_TOTAL_STEPS; i++){
		delayMs(20);
		GPIO_PortClear(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
		delayMs(20);
		GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
	}

	//disable potentiometer
	GPIO_PortSet(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
}

void SignalGen_setFrec(uint16_t frec){
	if(frec > 20000) return;
	currentFrec = frec;
}

uint8_t SignalGen_getDivisor(){
	return (1+(scale*100/SCALE_RES_VAL));
}

void SignalGen_stop(){
	dacSamples = 0;
	cylceCounter = 0;
	DAC_EnableCounter(DAC0_PERIPHERAL, false);
}

uint8_t SignalGen_getCycleCount(){
	return cylceCounter;
}

float SignalGen_getCurrPhase(){
	return dacSamples*360/DAC_SINE_RESOLUTION;
}

void SignalGen_run(){
	float timeStep = 1/(currentFrec*DAC_SINE_RESOLUTION);

	if(dacSamples==0){
		for(int i = 0; i < DAC_SINE_RESOLUTION; i++){
			float val = DAC_HALF_VALUE + SINE_AMPLITUDE * sinf(2*MPI*currentFrec*i*timeStep);
			DAC_SetBufferValue(DAC0_PERIPHERAL, val);
		}
		DAC_SetCounterValue(DAC0_PERIPHERAL, SECONDS_TO_DAC_VAL(timeStep));
		DAC_EnableCounter(DAC0_PERIPHERAL, true);
	}

}

/* DAC0_IRQn interrupt handler */
void DAC0_IRQHANDLER(void) {

	dacSamples++;
	if(dacSamples==DAC_SINE_RESOLUTION){
		dacSamples=0;
		cylceCounter++;
	}

	/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
	#if defined __CORTEX_M && (__CORTEX_M == 4U)
		__DSB();
	#endif
}

