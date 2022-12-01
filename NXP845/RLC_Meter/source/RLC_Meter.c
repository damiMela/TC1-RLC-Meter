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
#include <stdio.h>
#include "string.h"
#include "math.h"

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"

#include "globalTimer.h"
#include "signalReader.h"
#include "signalGenerator.h"
#include "UartComm.h"

#define BOARD_LED_PORT BOARD_INITLEDSPINS_LED_GREEN_PORT
#define BOARD_LED_PIN  BOARD_INITLEDSPINS_LED_GREEN_PIN

#define CURRENT_RES	560


typedef enum _state{
	INIT,
	STANDBY,
	MEASURE,
	PROCESS,
	CHANGE_FREQ,
	DONE
} state;

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
    POWER_DisablePD(kPDRUNCFG_PD_DAC0);
    SysTick_Config(SystemCoreClock / (1000-1));


    /* Program variables */
   state s = INIT;
   char uartCmd[UART_CMD_LEN] = {0};

   uint16_t signalMaxVal[2] = {0};
   uint16_t signalCurrVal[2] = {0};
   uint8_t 	signalMaxValPhase = 0;

   float realVal = 0, imgVal = 0, module = 0;
   char outputText[15] = "";

   timer_setValue(LED_TIMER, 1000);

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	SignalReader_updateReadings();
    	SignalGen_run();

    	//toggle led while working
		if(timer_getStatus(LED_TIMER)){
			GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
		}

		if(UartComm_cmdDetected()){
			UartComm_readCmd(uartCmd);
		}


		switch(s){
		case INIT:
			timer_reset(LED_TIMER); //keep LED off while initiating
			SignalGen_resetScale();
			SignalGen_stop();
			s = STANDBY;
			break;

		case STANDBY:
			if(strstr(uartCmd, "START") != NULL){
				uartCmd[0] = 0;
				s = MEASURE;
			}
			if(strstr(uartCmd, "CFREQ") != NULL){
				uartCmd[0] = 0;
				s = CHANGE_FREQ;
			}
			break;

		case CHANGE_FREQ:
			if(uartCmd[0] != 0){
				SignalGen_setFrec(atoi(uartCmd));
				uartCmd[0] = 0;
				s = STANDBY;
			}
			break;

		case MEASURE:
			if(SignalGen_getCycleCount() < 2){
				signalCurrVal[0] = SignalReader_readSample(SIGNAL1);
				signalCurrVal[1] = SignalReader_readSample(SIGNAL2);
				if(signalMaxVal[0] < signalCurrVal[0]){
					signalMaxVal[0]= signalCurrVal[0];
					signalMaxValPhase = SignalGen_getCurrPhase();
				}
				if(signalMaxVal[1] < signalCurrVal[1])
					signalMaxVal[1]= signalCurrVal[1];
			}
			else{
				SignalGen_stop();
				s = PROCESS;
			}
			break;

		case PROCESS:
			module = abs((signalMaxVal[0]- (signalMaxVal[1])/SignalGen_getDivisor()))/CURRENT_RES;
			realVal = module * cosf(signalMaxValPhase);
			imgVal = module * sinf(signalMaxValPhase);


			sprintf(outputText, "Z = %d+j%d",realVal, imgVal);
			break;
		default:
			break;
		}

    }
    return 0 ;
}
