/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    RLC_Meter.c
 * @brief   Application entry point.
 */
#include <signalReader.h>
#include <sineGenerator.h>
#include <stdio.h>
#include "string.h"
#include "math.h"

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"

#include "globalTimer.h"
#include "UartComm.h"

#define BOARD_LED_PORT BOARD_INITLEDSPINS_LED_GREEN_PORT
#define BOARD_LED_PIN  BOARD_INITLEDSPINS_LED_GREEN_PIN

#define CURRENT_RES	560


typedef enum _state{
	INIT,
	STANDBY,
	MEASURE,
	PROCESS,
	DONE
} state;

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif


    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    SysTick_Config(SystemCoreClock / (1000-1));
	timer_setValue(LED_TIMER, 1000);
	signalReader_init();



    /* Program variables */
   state s = INIT;
   float realVal = 0, imgVal = 0, module = 0;

   char uartCmd = 0;
   char outputText[50] = {0};

   uint16_t signalMaxVal[2] = {0};
   uint16_t signalCurrVal[2] = {0};
   uint8_t 	signalMaxValPhase = 0;

    while(1) {
    	signalReader_update();

    	//toggle led while working
		if(timer_getStatus(LED_TIMER)){
			GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
		}

		if(UartComm_cmdDetected()){
			uartCmd = UartComm_readCmd(uartCmd);
		}


		switch(s){
		case INIT:
			timer_reset(LED_TIMER); //keep LED off while initiating
			signalReader_resetScale();
			sineGenerator_stop();
			sineGenerator_freq(1000);
			s = STANDBY;
			break;

		case STANDBY:
			if(uartCmd == START_CMD){
				uartCmd = 0;
				sineGenerator_init();
				signalMaxVal[0]= 0;
				signalMaxVal[1]= 0;
				signalMaxValPhase = 0;
				s = MEASURE;
				signalReader_resetIndex();
				//wait for a new cycle to start
				while(!sineGenerator_CycleStarted())
					sineGenerator_resetCycleCount();
			}
			break;

		case MEASURE:
			if(sineGenerator_CycleStarted())
				signalReader_resetIndex();

			if(sineGenerator_getCycleCount() < 20){
				signalCurrVal[0] = signalReader_readSample(SIGNAL1);
				signalCurrVal[1] = signalReader_readSample(SIGNAL2);


				if(signalMaxVal[1] < signalCurrVal[1]){
					signalMaxVal[1]= signalCurrVal[1];
					signalMaxValPhase = signalReader_getPhaseFromIndex(SINE_FREC);
				}
			}
			else{
				sineGenerator_stop();
				if(signalMaxVal[1] < ADC_MAX_VAL){
					signalReader_incrementScale(true);
					sineGenerator_init();
				}
				else{
					signalReader_resetScale();
					s = PROCESS;
				}
			}
			break;

		case PROCESS:
			module = abs((signalMaxVal[0]- (signalMaxVal[1])/signalReader_getCurrentScale()))/CURRENT_RES;
			realVal = module * cosf(signalMaxValPhase);
			imgVal = module * sinf(signalMaxValPhase);

			sprintf(outputText, "Z = %d+j%d",realVal, imgVal);
			s = STANDBY;
			break;
		default:
			break;
		}

    }

    return 0 ;
}
