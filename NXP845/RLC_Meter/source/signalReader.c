#include "signalReader.h"

volatile uint32_t signals[2] = {0};
volatile bool sequenceReady = false;


void SignalReader_updateReadings(){
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
}

uint32_t SignalReader_readSample(signal_n signal){
	return signals[signal];
}

bool SignalReader_sampleReady(){
	if(sequenceReady){
		sequenceReady = false;
		return true;
	}
	return false;
}

void ADC0_ADC_SEQ_A_IRQHANDLER (void)
{
	if (kADC_ConvSeqAInterruptFlag == (ADC_GetStatusFlags(ADC0) & kADC_ConvSeqAInterruptFlag))
	{
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);

		adc_result_info_t adc_channels[2];
		ADC_GetChannelConversionResult(ADC0, 0, &adc_channels[0]);
		ADC_GetChannelConversionResult(ADC0, 1, &adc_channels[1]);
		signals[0] = adc_channels[0].result;
		signals[1] = adc_channels[1].result;
		sequenceReady = true;
	}
}


