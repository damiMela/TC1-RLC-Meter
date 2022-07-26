/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v11.0
processor: LPC845
package_id: LPC845M301JBD48
mcu_data: ksdk2_0
processor_version: 12.0.0
board: LPC845BREAKOUT
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: a1bf1abb-ba15-4a89-8c58-09436b4ba743
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * ADC0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'ADC0'
- type: 'lpc_adc'
- mode: 'ADC'
- custom_name_enabled: 'false'
- type_id: 'lpc_adc_d74172b5bd0591c0d32a6c93c043a67f'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'ADC0'
- config_sets:
  - fsl_adc:
    - doSelfCalibration: 'false'
    - adcConfig:
      - clockMode: 'kADC_ClockSynchronousMode'
      - clockSourceFreq: 'BOARD_BootClockFRO18M'
      - clockDividerNumber: '0'
      - enableLowPowerMode: 'false'
      - voltageRange: 'kADC_HighVoltageRange'
    - thresholdConfig:
      - ADC_SetThreshold0: 'false'
      - thresholdSettingsPair0:
        - lowValue: '0'
        - highValue: '0'
      - ADC_SetThreshold1: 'false'
      - thresholdSettingsPair1:
        - lowValue: '0'
        - highValue: '0'
    - enableSeqConfigurationA: 'true'
    - adcConvSeqConfigA:
      - enableHighPriority: 'false'
      - adcConvSeqConfig:
        - triggerMaskM: '0U'
        - triggerPolarity: 'kADC_TriggerPolarityNegativeEdge'
        - enableSyncBypass: 'false'
        - enableSingleStep: 'false'
        - interruptMode: 'kADC_InterruptForEachSequence'
    - enableSeqConfigurationB: 'false'
    - adcConvSeqConfigB:
      - enableHighPriority: 'false'
      - adcConvSeqConfig:
        - triggerMaskM: '0U'
        - triggerPolarity: 'kADC_TriggerPolarityNegativeEdge'
        - enableSyncBypass: 'false'
        - enableSingleStep: 'false'
        - interruptMode: 'kADC_InterruptForEachConversion'
    - channels:
      - 0:
        - channelName: ''
        - channelNumber: 'CH.0'
        - channelThresholdPair: 'thresholdPair0'
        - thresholdInterruptMode: 'kADC_ThresholdInterruptDisabled'
        - conversion_sequence: 'a'
      - 1:
        - channelName: ''
        - channelNumber: 'CH.1'
        - channelThresholdPair: 'thresholdPair0'
        - thresholdInterruptMode: 'kADC_ThresholdInterruptDisabled'
        - conversion_sequence: 'a'
    - interrupt_sel: 'kADC_ConvSeqAInterruptEnable'
    - enable_irq_seqA: 'true'
    - adc_interrupt_seqA:
      - IRQn: 'ADC0_SEQA_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_seqB: 'false'
    - adc_interrupt_seqB:
      - IRQn: 'ADC0_SEQB_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_thcmp: 'false'
    - adc_interrupt_thcmp:
      - IRQn: 'ADC0_THCMP_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - enable_irq_ovr: 'false'
    - adc_interrupt_ovr:
      - IRQn: 'ADC0_OVR_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const adc_config_t ADC0configStruct = {
  .clockMode = kADC_ClockSynchronousMode,
  .clockDividerNumber = 0UL,
  .enableLowPowerMode = false,
  .voltageRange = kADC_HighVoltageRange,
};
/* Conversion sequence A configuration structure */
const adc_conv_seq_config_t ADC0ConvSeqAConfigStruct = {
  .channelMask = 1U | 2U,
  .triggerMask = 0U,
  .triggerPolarity = kADC_TriggerPolarityNegativeEdge,
  .enableSyncBypass = false,
  .enableSingleStep = false,
  .interruptMode = kADC_InterruptForEachSequence
};

static void ADC0_init(void) {
  /* Initialize ADC0 peripheral */
  ADC_Init(ADC0_PERIPHERAL, &ADC0configStruct);
  /* Configure the conversion sequence A */
  ADC_SetConvSeqAConfig(ADC0_PERIPHERAL, &ADC0ConvSeqAConfigStruct);
  /* Enable the conversion sequence A */
  ADC_EnableConvSeqA(ADC0_PERIPHERAL, true);
  /* Enable interrupt from ADC */
  ADC_EnableInterrupts(ADC0_PERIPHERAL, kADC_ConvSeqAInterruptEnable);
  /* Configure threshold compare interrupt on channel 0 */
  ADC_EnableThresholdCompareInterrupt(ADC0_PERIPHERAL, 0U, kADC_ThresholdInterruptDisabled);
  /* Configure threshold compare interrupt on channel 1 */
  ADC_EnableThresholdCompareInterrupt(ADC0_PERIPHERAL, 1U, kADC_ThresholdInterruptDisabled);
  /* Enable interrupt ADC0_SEQA_IRQn request in the NVIC. */
  EnableIRQ(ADC0_ADC_SEQ_A_IRQN);
}

/***********************************************************************************************************************
 * USART0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'USART0'
- type: 'lpc_miniusart'
- mode: 'polling'
- custom_name_enabled: 'false'
- type_id: 'lpc_miniusart_78c250a8cd7edc52679c826bef63c9a6'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'USART0'
- config_sets:
  - fsl_usart:
    - usartConfig:
      - clockSource: 'FunctionClock'
      - clockSourceFreq: 'BOARD_BootClockFRO18M'
      - baudRate_Bps: '9600'
      - syncMode: 'kUSART_SyncModeDisabled'
      - parityMode: 'kUSART_ParityDisabled'
      - stopBitCount: 'kUSART_OneStopBit'
      - bitCountPerChar: 'kUSART_8BitsPerChar'
      - loopback: 'false'
      - enableRx: 'true'
      - enableTx: 'true'
      - clockPolarity: 'kUSART_RxSampleOnFallingEdge'
      - enableContinuousSCLK: 'false'
      - enableHardwareFlowControl: 'false'
    - quick_selection: 'QS_USART_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const usart_config_t USART0_config = {
  .baudRate_Bps = 9600UL,
  .syncMode = kUSART_SyncModeDisabled,
  .parityMode = kUSART_ParityDisabled,
  .stopBitCount = kUSART_OneStopBit,
  .bitCountPerChar = kUSART_8BitsPerChar,
  .loopback = false,
  .enableRx = true,
  .enableTx = true,
  .clockPolarity = kUSART_RxSampleOnFallingEdge,
  .enableContinuousSCLK = false,
  .enableHardwareFlowControl = false
};

static void USART0_init(void) {
  /* USART0 peripheral initialization */
  USART_Init(USART0_PERIPHERAL, &USART0_config, USART0_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * DAC0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DAC0'
- type: 'lpc_dac'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'lpc_dac_be609e98c6bf7f417ccc66d577e5bc39'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DAC0'
- config_sets:
  - general:
    - general_config:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'BOARD_BootClockFRO30M'
      - settlingTime: 'kDAC_SettlingTimeIs1us'
    - enable_double_buffer: 'true'
    - buffer_value_input: '0'
    - counter_value_input: '0'
    - enable_dma: 'false'
    - enable_counter: 'true'
    - enableInterrupt: 'true'
    - interrupt:
      - IRQn: 'DAC0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const dac_config_t DAC0_config = {
  .settlingTime = kDAC_SettlingTimeIs1us
};

static void DAC0_init(void) {
  /* DAC0 initiation  */
  DAC_Init(DAC0_PERIPHERAL, &DAC0_config);
  /* DAC0 double buffering enabled */
  DAC_EnableDoubleBuffering(DAC0_PERIPHERAL, true);
  /* DAC0 set buffer value */
  DAC_SetBufferValue(DAC0_PERIPHERAL, DAC0_BUFFER_VALUE);
  /* DAC0 set counter value */
  DAC_SetCounterValue(DAC0_PERIPHERAL, DAC0_COUNTER_VALUE);
  /* Enable interrupt DAC0_IRQn request in the NVIC. */
  EnableIRQ(DAC0_IRQN);
  /* DAC0 enable counter */
  DAC_EnableCounter(DAC0_PERIPHERAL, true);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  ADC0_init();
  USART0_init();
  DAC0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
