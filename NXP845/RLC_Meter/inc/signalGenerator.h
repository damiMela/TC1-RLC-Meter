/*
 * generator.h
 *
 *  Created on: 17 nov. 2022
 *      Author: Damian - PC
 */

#ifndef HEADERS_GENERATOR_H_
#define HEADERS_GENERATOR_H_

#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_dac.h"
#include "fsl_ctimer.h"
#include "globalTimer.h"
#include "peripherals.h"

#ifndef MPI
#define MPI 3.14159265358979323846
#endif

#define DAC_CTIMER			CTIMER0_PERIPHERAL

#define POT_VALUE			10000
#define POT_STEP			100
#define POT_TOTAL_STEPS		POT_VALUE/POT_STEP

#define DAC_HALF_VALUE	512
#define SINE_AMPLITUDE	480
#define DAC_SINE_RESOLUTION	49
#define SECONDS_TO_DAC_VAL(x)	(int)(1000000*x*30)

#define  SCALE_RES_VAL 33

void SignalGen_resetScale();
void SignalGen_setScale(uint8_t scale);
void SignalGen_setFrec(uint16_t frec);
void SignalGen_stop();
uint8_t SignalGen_getCycleCount();
float SignalGen_getCurrPhase();
void SignalGen_run();
void DAC0_IRQHANDLER(void);

#endif /* HEADERS_GENERATOR_H_ */
