/*
 * singalReader.h
 *
 *  Created on: 19 nov. 2022
 *      Author: Damian - PC
 */

#ifndef SIGNALREADER_H_
#define SIGNALREADER_H_

#include "fsl_adc.h"
#include "peripherals.h"
#include "globalTimer.h"
typedef enum{
	SIGNAL1,
	SIGNAL2,
	_TOTAL_SIGNALS
} signal_n;

#define SINGAL_SAMPLES_PER_SECOND 100

void ADC0_ADC_SEQ_A_IRQHANDLER (void);
void SignalReader_updateReadings();
bool SignalReader_sampleReady();
uint32_t SignalReader_readSample(signal_n signal);
uint32_t SignalReader_read(uint16_t *s1, uint16_t *s2, uint16_t len);

#endif /* SIGNALREADER_H_ */
