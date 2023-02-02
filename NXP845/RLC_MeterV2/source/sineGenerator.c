/*
 * sine_generator.c
 *
 *  Created on: 17 nov. 2022
 *      Author: Damian - PC
 */
#include <sineGenerator.h>


#include "peripherals.h"
#include  "math.h"
#include "fsl_dac.h"
#include "fsl_dma.h"
#include "fsl_power.h"

volatile uint8_t dacSamples = 0;
uint8_t cylceCounter = 0;
uint16_t currentFrec;

volatile uint8_t index = 0;
volatile bool RunSignal_f = false, cycleStarted_f = false;
volatile int cycleCounter = 0;
static int frec = 0;

/*
static const uint32_t SinusOutputData[SINE_RESOLUTION] = {
		512,577,641,704,763,818,868,912,949,980,1002,1017,
		1023,1021,1011,992,965,931,891,843,791,734,673,609,
		544,479,414,350,289,232,180,132,92,58,31,12,2,0,6,
		21,43,74,111,155,205,260,319,382,446,511
};
*/

//static const
/*uint32_t SinusOutputData[100]={
		32768,34822,36867,38896,40901,42874,44807,46693,48523,
		50292,51991,53614,55155,56608,57967,59226,60381,61427,
		62359,63175,63871,64445,64893,65214,65407,65472,65407,
		65214,64893,64445,63871,63175,62359,61427,60381,59226,
		57967,56608,55155,53614,51991,50292,48523,46693,44807,
		42874,40901,38896,36867,34822,32768,30714,28669,26640,
		24635,22662,20729,18843,17013,15244,13545,11922,10381,
		8928,7569,6310,5155,4109,3177,2361,1665,1091,643,322,
		129,64,129,322,643,1091,1665,2361,3177,4109,5155,6310,
		7569,8928,10381,11922,13545,15244,17013,18843,20729,
		22662,24635,26640,28669,30714

};*/
uint32_t SinusOutputData[100]={
		51577,53166,54674,56095,57424,58657,59786,60810,61722,62521,63202,63763,64201,64516,64705,64768,64705,64516,64201,63763,63202,62521,61722,60810,59786,58657,57424,56095,54674,53166,51577,49914,48184,46393,44548,42657,40726,38764,36779,34777,32768,30759,28757,26772,24810,22879,20988,19143,17352,15622,13959,12370,10862,9441,8112,6879,5750,4726,3814,3015,2334,1773,1335,1020,831,768,831,1020,1335,1773,2334,3015,3814,4726,5750,6879,8112,9441,10862,12370,13959,15622,17352,19143,20988,22879,24810,26772,28757,30759,32768,34777,36779,38764,40726,42657,44548,46393,48184,49914
};

void sineGenerator_init(void)
{
	//DAC_SetCounterValue(DAC0, SINE_COUNTER_VAL);
	POWER_DisablePD(kPDRUNCFG_PD_DAC0);
	DMA_StartTransfer(&DMA0_CH0_Handle);
	RunSignal_f = true;
}

void sineGenerator_stop(){
	POWER_EnablePD(kPDRUNCFG_PD_DAC0);
	RunSignal_f = false;
	cycleCounter=0;
}

void sineGenerator_freq(uint32_t value)
{
	frec = value;
	DAC_SetCounterValue(DAC0, value*30);
}


uint8_t sineGenerator_getCycleCount(){
	return cycleCounter;
}

void sineGenerator_resetCycleCount(){
	cycleCounter=0;
}

bool sineGenerator_CycleStarted(){
	if(cycleStarted_f){
		cycleStarted_f = false;
		return true;
	}
	return false;
}

void DAC_DMA_Callback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds) {

	if(tcds == kDMA_IntA){
		cycleCounter++;
		cycleStarted_f = true;
	}

	if(RunSignal_f)
		DMA_StartTransfer(&DMA0_CH0_Handle);

}

