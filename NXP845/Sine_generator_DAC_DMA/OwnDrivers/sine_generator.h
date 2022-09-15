/*
 * sine_generator.h
 *
 *  Created on: 7 sep. 2022
 *      Author: juan
 */

#ifndef SINE_GENERATOR_H_
#define SINE_GENERATOR_H_

#include <stdint.h>
#include "LPC845.h"


void sine_generator_init(void);
void sine_generator_send(uint32_t value);
void sine_generator_freq(uint32_t value); //value 30:1MHz 300:100kHz 3000:10kHz  30000:1kHz
void DAC0_IRQHandler(void);



#endif /* SINE_GENERATOR_H_ */
