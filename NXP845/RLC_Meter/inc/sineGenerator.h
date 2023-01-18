/*
 * sine_generator.h
 *
 *  Created on: 17 nov. 2022
 *      Author: Damian - PC
 */

#ifndef HEADERS_GENERATOR_H_
#define HEADERS_GENERATOR_H_

#include "board.h"

#ifndef MPI
#define MPI 3.14159265358979323846
#endif


#define DAC_HALF_VALUE	512
#define SINE_AMPLITUDE	480
#define SINE_RESOLUTION	100
#define SECONDS_TO_DAC_VAL(x)	(int)(1000000*x*30)

#define  SCALE_RES_VAL 33


void sineGenerator_init(void);
void sineGenerator_stop(void);
void sineGenerator_send(uint32_t value);
void sineGenerator_freq(uint32_t value);
void sineGenerator_resetCycleCount();
uint8_t sineGenerator_getPhase();
uint8_t sineGenerator_getCycleCount();
void DAC0_IRQHANDLER(void);

#endif /* HEADERS_GENERATOR_H_ */
