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
processor_version: 11.0.1
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
 * DMA0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DMA0'
- type: 'lpc_dma'
- mode: 'basic'
- custom_name_enabled: 'false'
- type_id: 'lpc_dma_c13ca997a68f2ca6c666916ba13db7d7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DMA0'
- config_sets:
  - fsl_dma:
    - dma_table: []
    - dma_channels: []
    - init_interrupt: 'false'
    - dma_interrupt:
      - IRQn: 'DMA0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void DMA0_init(void) {
} */

/***********************************************************************************************************************
 * DAC0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DAC0'
- type: 'dac'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'lpc_dac_92ab025aef483f7b5beccd75a79dd0ec'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DAC0'
- config_sets:
  - general:
    - general_config:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'BOARD_BootClockFRO30M'
      - settlingTime: 'kDAC_SettlingTimeIs1us'
    - enable_double_buffer: 'false'
    - buffer_value_input: '0'
    - counter_value_input: '120'
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
  /* Global initialization */
  DMA_Init(DMA0_DMA_BASEADDR);

  /* Initialize components */
  DAC0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
