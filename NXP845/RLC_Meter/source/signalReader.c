#include <signalReader.h>

#include "peripherals.h"
#include "sineGenerator.h"
#include "globalTimer.h"
#include "fsl_power.h"
#include "fsl_adc.h"
#include "pin_mux.h"


volatile uint32_t signals[2] = {0};
volatile bool sequenceReady = false;
uint8_t currentScale = 0;

void signalReader_init(){
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
}

void signalReader_stop(){
    POWER_EnablePD(kPDRUNCFG_PD_ADC0);
}

void signalReader_update(){
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
}

uint32_t signalReader_readSample(signal_n signal){
	return signals[signal];
}

bool signalReader_sampleReady(){
	if(sequenceReady){
		sequenceReady = false;
		return true;
	}
	return false;
}


void signalReader_setScale(uint8_t scale){
	if((scale > 100) || (scale == currentScale)) return;

	//enable potentiometer
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);

	if(scale > currentScale){
		for(int i=currentScale; i<scale; i++){
			signalReader_incrementScale(true);
			scale++;
		}
	}
	else{
		for(int i=currentScale; i>scale; i--){
			signalReader_incrementScale(false);
			scale--;
		}
	}

	//disable potentiometer
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
}

void signalReader_resetScale(){
	//set potentiometer to "enable, down mode, keep value"
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
	GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);

	for(int i=0; i<POT_TOTAL_STEPS; i++){
		signalReader_incrementScale(false);
	}

	//disable potentiometer
	GPIO_PortSet(GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN_MASK);
}

void signalReader_incrementScale(bool up){
	if(up)GPIO_PortSet(GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN_MASK);
	else GPIO_PortClear(GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN_MASK);

	delayMs(20);
	GPIO_PortClear(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
	delayMs(20);
	GPIO_PortSet(GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN_MASK);
}

uint16_t signalReader_getCurrentScale(){
	return currentScale;
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


