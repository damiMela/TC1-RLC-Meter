/*
 * singalReader.h
 *
 *  Created on: 19 nov. 2022
 *      Author: Damian - PC
 */

#ifndef SIGNALREADER_H_
#define SIGNALREADER_H_

#include "board.h"

typedef enum{
	SIGNAL1,
	SIGNAL2,
	_TOTAL_SIGNALS
} signal_n;


#define POT_VALUE			10000
#define POT_STEP			100
#define POT_TOTAL_STEPS		POT_VALUE/POT_STEP
#define ADC_MAX_VAL			3000

void signalReader_setup();
void signalReader_init();
void signalReader_stop();

void signalReader_update();
bool signalReader_sampleReady();
uint32_t signalReader_readSample(signal_n signal);
uint32_t signalReader_read(uint16_t *s1, uint16_t *s2, uint16_t len);

void signalReader_setScale(uint8_t scale);
void signalReader_resetScale();
void signalReader_incrementScale(bool up);
uint16_t signalReader_getCurrentScale();

void signalReader_resetIndex();
uint16_t signalReader_getPhaseFromIndex(uint16_t singalFrec);

void ADC0_ADC_SEQ_A_IRQHANDLER (void);

#endif /* SIGNALREADER_H_ */
