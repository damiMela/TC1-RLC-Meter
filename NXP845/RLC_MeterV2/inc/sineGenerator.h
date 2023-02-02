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


#define DAC_HALF_VALUE	512U
#define SINE_AMPLITUDE	480U
#define SINE_RESOLUTION	5

#define  SCALE_RES_VAL 33

#define SINE_FREC 1000U
#define SINE_COUNTER_VAL SINE_FREC*30

void sineGenerator_init(void);
void sineGenerator_stop(void);
void sineGenerator_send(uint32_t value);
void sineGenerator_freq(uint32_t value);
void sineGenerator_resetCycleCount();
uint8_t sineGenerator_getCycleCount();
bool sineGenerator_CycleStarted();
void DAC0_IRQHANDLER(void);

#endif /* HEADERS_GENERATOR_H_ */
