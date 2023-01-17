/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: LPC845
package_id: LPC845M301JBD48
mcu_data: ksdk2_0
processor_version: 12.0.0
board: LPC845BREAKOUT
pin_labels:
- {pin_num: '2', pin_signal: PIO0_13/ADC_10, label: 'CN1[26]/PIO0_13/ADC_10', identifier: POT_UD;POT_INC}
- {pin_num: '12', pin_signal: PIO0_11/I2C0_SDA, label: 'CN1[24]/PIO0_11/I2C0_SDA', identifier: POT_CS}
- {pin_num: '21', pin_signal: PIO1_3/CAPT_X4, label: PIO1_3/CAPT_X4, identifier: POT_CS;POT_CS_}
- {pin_num: '22', pin_signal: PIO0_15, label: 'CN1[28]/PIO0_15', identifier: POT_CS}
- {pin_num: '23', pin_signal: PIO1_4/CAPT_X5, label: PIO1_4/CAPT_X5, identifier: POT_INC;POT_INC_}
- {pin_num: '27', pin_signal: PIO1_5/CAPT_X6, label: PIO1_5/CAPT_X6, identifier: POT_UD;POT_UD_}
- {pin_num: '37', pin_signal: PIO0_14/ACMP_I3/ADC_2, label: 'CN1[27]/PIO0_14/ACMP_I3/ADC_2', identifier: POT_INC;POT_INC_;POT_UD}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_swm.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitLEDsPins();
    BOARD_InitDEBUG_UARTPins();
    BOARD_InitSWD_DEBUGPins();
    BOARD_InitBUTTONsPins();
    BOARD_InitCAPTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '33', peripheral: ADC0, signal: 'CH, 0', pin_signal: PIO0_7/ADC_0}
  - {pin_num: '34', peripheral: ADC0, signal: 'CH, 1', pin_signal: PIO0_6/ADC_1/ACMPVREF}
  - {pin_num: '48', peripheral: DAC0, signal: DACOUT0, pin_signal: PIO0_17/ADC_9/DACOUT_0, dacmode: enabled}
  - {pin_num: '37', peripheral: GPIO, signal: 'PIO0, 14', pin_signal: PIO0_14/ACMP_I3/ADC_2, identifier: POT_UD, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: '2', peripheral: GPIO, signal: 'PIO0, 13', pin_signal: PIO0_13/ADC_10, identifier: POT_INC, direction: OUTPUT, mode: pullDown}
  - {pin_num: '12', peripheral: GPIO, signal: 'PIO0, 11', pin_signal: PIO0_11/I2C0_SDA, direction: OUTPUT, gpio_init_state: 'true', invert: disabled, i2cmode: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    gpio_pin_config_t POT_CS_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO0_11 (pin 12)  */
    GPIO_PinInit(BOARD_INITPINS_POT_CS_GPIO, BOARD_INITPINS_POT_CS_PORT, BOARD_INITPINS_POT_CS_PIN, &POT_CS_config);

    gpio_pin_config_t POT_INC_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U,
    };
    /* Initialize GPIO functionality on pin PIO0_13 (pin 2)  */
    GPIO_PinInit(BOARD_INITPINS_POT_INC_GPIO, BOARD_INITPINS_POT_INC_PORT, BOARD_INITPINS_POT_INC_PIN, &POT_INC_config);

    gpio_pin_config_t POT_UD_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO0_14 (pin 37)  */
    GPIO_PinInit(BOARD_INITPINS_POT_UD_GPIO, BOARD_INITPINS_POT_UD_PORT, BOARD_INITPINS_POT_UD_PIN, &POT_UD_config);

    IOCON->PIO[7] = ((IOCON->PIO[7] &
                      /* Mask bits to zero which are setting */
                      (~(IOCON_PIO_INV_MASK)))

                     /* Invert input: Input not inverted (HIGH on pin reads as 1; LOW on pin reads as 0). */
                     | IOCON_PIO_INV(PIO0_11_INV_NOT_INVERTED));

    IOCON->PIO[1] = ((IOCON->PIO[1] &
                      /* Mask bits to zero which are setting */
                      (~(IOCON_PIO_MODE_MASK)))

                     /* Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-down. Pull-down
                      * resistor enabled. */
                     | IOCON_PIO_MODE(PIO0_13_MODE_PULL_DOWN));

    IOCON->PIO[0] = ((IOCON->PIO[0] &
                      /* Mask bits to zero which are setting */
                      (~(IOCON_PIO_DACMODE_MASK)))

                     /* DAC mode enable.: Enable. */
                     | IOCON_PIO_DACMODE(PIO0_17_DACMODE_ENABLE));

    /* ADC_CHN0 connect to P0_7 */
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);

    /* ADC_CHN1 connect to P0_6 */
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN1, true);

    /* DACOUT0 connect to P0_17 */
    SWM_SetFixedPinSelect(SWM0, kSWM_DAC_OUT0, true);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '11', peripheral: GPIO, signal: 'PIO1, 0', pin_signal: PIO1_0/CAPT_X1, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled,
    hysteresis: enabled, opendrain: disabled, smode: bypass, clkdiv: div0}
  - {pin_num: '14', peripheral: GPIO, signal: 'PIO1, 1', pin_signal: PIO1_1/CAPT_X2, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled,
    hysteresis: enabled, opendrain: disabled, smode: bypass, clkdiv: div0}
  - {pin_num: '16', peripheral: GPIO, signal: 'PIO1, 2', pin_signal: PIO1_2/CAPT_X3, direction: OUTPUT, gpio_init_state: 'true', mode: inactive, invert: disabled,
    hysteresis: enabled, opendrain: disabled, smode: bypass, clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitLEDsPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO1 module */
    CLOCK_EnableClock(kCLOCK_Gpio1);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO1_0 (pin 11)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_GREEN_GPIO, BOARD_INITLEDSPINS_LED_GREEN_PORT, BOARD_INITLEDSPINS_LED_GREEN_PIN, &LED_GREEN_config);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO1_1 (pin 14)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_BLUE_GPIO, BOARD_INITLEDSPINS_LED_BLUE_PORT, BOARD_INITLEDSPINS_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U,
    };
    /* Initialize GPIO functionality on pin PIO1_2 (pin 16)  */
    GPIO_PinInit(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, &LED_RED_config);

    const uint32_t LED_GREEN = (/* No addition pin function */
                                IOCON_PIO_MODE_INACT |
                                /* Enable hysteresis */
                                IOCON_PIO_HYS_EN |
                                /* Input not invert */
                                IOCON_PIO_INV_DI |
                                /* Disables Open-drain function */
                                IOCON_PIO_OD_DI |
                                /* Bypass input filter */
                                IOCON_PIO_SMODE_BYPASS |
                                /* IOCONCLKDIV0 */
                                IOCON_PIO_CLKDIV0);
    /* PIO1 PIN0 (coords: 11) is configured as GPIO, PIO1, 0. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_0, LED_GREEN);

    const uint32_t LED_BLUE = (/* No addition pin function */
                               IOCON_PIO_MODE_INACT |
                               /* Enable hysteresis */
                               IOCON_PIO_HYS_EN |
                               /* Input not invert */
                               IOCON_PIO_INV_DI |
                               /* Disables Open-drain function */
                               IOCON_PIO_OD_DI |
                               /* Bypass input filter */
                               IOCON_PIO_SMODE_BYPASS |
                               /* IOCONCLKDIV0 */
                               IOCON_PIO_CLKDIV0);
    /* PIO1 PIN1 (coords: 14) is configured as GPIO, PIO1, 1. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_1, LED_BLUE);

    const uint32_t LED_RED = (/* No addition pin function */
                              IOCON_PIO_MODE_INACT |
                              /* Enable hysteresis */
                              IOCON_PIO_HYS_EN |
                              /* Input not invert */
                              IOCON_PIO_INV_DI |
                              /* Disables Open-drain function */
                              IOCON_PIO_OD_DI |
                              /* Bypass input filter */
                              IOCON_PIO_SMODE_BYPASS |
                              /* IOCONCLKDIV0 */
                              IOCON_PIO_CLKDIV0);
    /* PIO1 PIN2 (coords: 16) is configured as GPIO, PIO1, 2. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_2, LED_RED);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '19', peripheral: USART0, signal: TXD, pin_signal: PIO0_25, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '20', peripheral: USART0, signal: RXD, pin_signal: PIO0_24, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t DEBUG_UART_RX = (/* Selects pull-up function */
                                    IOCON_PIO_MODE_PULLUP |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI |
                                    /* Bypass input filter */
                                    IOCON_PIO_SMODE_BYPASS |
                                    /* IOCONCLKDIV0 */
                                    IOCON_PIO_CLKDIV0);
    /* PIO0 PIN24 (coords: 20) is configured as USART0, RXD. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_24, DEBUG_UART_RX);

    const uint32_t DEBUG_UART_TX = (/* Selects pull-up function */
                                    IOCON_PIO_MODE_PULLUP |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI |
                                    /* Bypass input filter */
                                    IOCON_PIO_SMODE_BYPASS |
                                    /* IOCONCLKDIV0 */
                                    IOCON_PIO_CLKDIV0);
    /* PIO0 PIN25 (coords: 19) is configured as USART0, TXD. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_25, DEBUG_UART_TX);

    /* USART0_TXD connect to P0_25 */
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P0_25);

    /* USART0_RXD connect to P0_24 */
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P0_24);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSWD_DEBUGPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '10', peripheral: SWD, signal: SWDIO, pin_signal: SWDIO/PIO0_2, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '8', peripheral: SWD, signal: SWCLK, pin_signal: SWCLK/PIO0_3, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '5', peripheral: SYSCON, signal: RESETN, pin_signal: RESETN/PIO0_5, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSWD_DEBUGPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitSWD_DEBUGPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t IOCON_INDEX_PIO0_2_config = (/* Selects pull-up function */
                                                IOCON_PIO_MODE_PULLUP |
                                                /* Enable hysteresis */
                                                IOCON_PIO_HYS_EN |
                                                /* Input not invert */
                                                IOCON_PIO_INV_DI |
                                                /* Disables Open-drain function */
                                                IOCON_PIO_OD_DI |
                                                /* Bypass input filter */
                                                IOCON_PIO_SMODE_BYPASS |
                                                /* IOCONCLKDIV0 */
                                                IOCON_PIO_CLKDIV0);
    /* PIO0 PIN2 (coords: 10) is configured as SWD, SWDIO. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_2, IOCON_INDEX_PIO0_2_config);

    const uint32_t IOCON_INDEX_PIO0_3_config = (/* Selects pull-up function */
                                                IOCON_PIO_MODE_PULLUP |
                                                /* Enable hysteresis */
                                                IOCON_PIO_HYS_EN |
                                                /* Input not invert */
                                                IOCON_PIO_INV_DI |
                                                /* Disables Open-drain function */
                                                IOCON_PIO_OD_DI |
                                                /* Bypass input filter */
                                                IOCON_PIO_SMODE_BYPASS |
                                                /* IOCONCLKDIV0 */
                                                IOCON_PIO_CLKDIV0);
    /* PIO0 PIN3 (coords: 8) is configured as SWD, SWCLK. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_3, IOCON_INDEX_PIO0_3_config);

    const uint32_t K2 = (/* Selects pull-up function */
                         IOCON_PIO_MODE_PULLUP |
                         /* Enable hysteresis */
                         IOCON_PIO_HYS_EN |
                         /* Input not invert */
                         IOCON_PIO_INV_DI |
                         /* Disables Open-drain function */
                         IOCON_PIO_OD_DI |
                         /* Bypass input filter */
                         IOCON_PIO_SMODE_BYPASS |
                         /* IOCONCLKDIV0 */
                         IOCON_PIO_CLKDIV0);
    /* PIO0 PIN5 (coords: 5) is configured as SYSCON, RESETN. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_5, K2);

    /* SWCLK connect to P0_3 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWCLK, true);

    /* SWDIO connect to P0_2 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWDIO, true);

    /* RESETN connect to P0_5 */
    SWM_SetFixedPinSelect(SWM0, kSWM_RESETN, true);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONsPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '6', peripheral: GPIO, signal: 'PIO0, 4', pin_signal: PIO0_4/ADC_11, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled,
    smode: bypass, clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitBUTTONsPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    gpio_pin_config_t K3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U,
    };
    /* Initialize GPIO functionality on pin PIO0_4 (pin 6)  */
    GPIO_PinInit(BOARD_INITBUTTONSPINS_K3_GPIO, BOARD_INITBUTTONSPINS_K3_PORT, BOARD_INITBUTTONSPINS_K3_PIN, &K3_config);

    const uint32_t K3 = (/* Selects pull-up function */
                         IOCON_PIO_MODE_PULLUP |
                         /* Enable hysteresis */
                         IOCON_PIO_HYS_EN |
                         /* Input not invert */
                         IOCON_PIO_INV_DI |
                         /* Disables Open-drain function */
                         IOCON_PIO_OD_DI |
                         /* Bypass input filter */
                         IOCON_PIO_SMODE_BYPASS |
                         /* IOCONCLKDIV0 */
                         IOCON_PIO_CLKDIV0);
    /* PIO0 PIN4 (coords: 6) is configured as GPIO, PIO0, 4. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_4, K3);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitCAPTPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '1', peripheral: CAPT, signal: CAPTYL, pin_signal: PIO1_8/CAPT_YL, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '3', peripheral: CAPT, signal: CAPTYH, pin_signal: PIO1_9/CAPT_YH, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
  - {pin_num: '9', peripheral: CAPT, signal: 'CAPTX, 0', pin_signal: PIO0_31/CAPT_X0, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled,
    smode: bypass, clkdiv: div0}
  - {pin_num: '42', peripheral: ACMP, signal: ACMP_IN5, pin_signal: PIO0_30/ACMP_I5, mode: inactive, invert: disabled, hysteresis: enabled, opendrain: disabled, smode: bypass,
    clkdiv: div0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitCAPTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitCAPTPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t CAPY_R = (/* No addition pin function */
                             IOCON_PIO_MODE_INACT |
                             /* Enable hysteresis */
                             IOCON_PIO_HYS_EN |
                             /* Input not invert */
                             IOCON_PIO_INV_DI |
                             /* Disables Open-drain function */
                             IOCON_PIO_OD_DI |
                             /* Bypass input filter */
                             IOCON_PIO_SMODE_BYPASS |
                             /* IOCONCLKDIV0 */
                             IOCON_PIO_CLKDIV0);
    /* PIO0 PIN30 (coords: 42) is configured as ACMP, ACMP_IN5. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_30, CAPY_R);

    const uint32_t CAPX = (/* No addition pin function */
                           IOCON_PIO_MODE_INACT |
                           /* Enable hysteresis */
                           IOCON_PIO_HYS_EN |
                           /* Input not invert */
                           IOCON_PIO_INV_DI |
                           /* Disables Open-drain function */
                           IOCON_PIO_OD_DI |
                           /* Bypass input filter */
                           IOCON_PIO_SMODE_BYPASS |
                           /* IOCONCLKDIV0 */
                           IOCON_PIO_CLKDIV0);
    /* PIO0 PIN31 (coords: 9) is configured as CAPT, CAPTX, 0. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_31, CAPX);

    const uint32_t CAPY_LOW = (/* No addition pin function */
                               IOCON_PIO_MODE_INACT |
                               /* Enable hysteresis */
                               IOCON_PIO_HYS_EN |
                               /* Input not invert */
                               IOCON_PIO_INV_DI |
                               /* Disables Open-drain function */
                               IOCON_PIO_OD_DI |
                               /* Bypass input filter */
                               IOCON_PIO_SMODE_BYPASS |
                               /* IOCONCLKDIV0 */
                               IOCON_PIO_CLKDIV0);
    /* PIO1 PIN8 (coords: 1) is configured as CAPT, CAPTYL. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_8, CAPY_LOW);

    const uint32_t CAPY_HIGH = (/* No addition pin function */
                                IOCON_PIO_MODE_INACT |
                                /* Enable hysteresis */
                                IOCON_PIO_HYS_EN |
                                /* Input not invert */
                                IOCON_PIO_INV_DI |
                                /* Disables Open-drain function */
                                IOCON_PIO_OD_DI |
                                /* Bypass input filter */
                                IOCON_PIO_SMODE_BYPASS |
                                /* IOCONCLKDIV0 */
                                IOCON_PIO_CLKDIV0);
    /* PIO1 PIN9 (coords: 3) is configured as CAPT, CAPTYH. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_9, CAPY_HIGH);

    /* ACMP_INPUT5 connect to P0_30 */
    SWM_SetFixedPinSelect(SWM0, kSWM_ACMP_INPUT5, true);

    /* CAPT_X0 connect to P0_31 */
    SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_X0, true);

    /* CAPT_YL connect to P1_8 */
    SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_YL, true);

    /* CAPT_YH connect to P1_9 */
    SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_YH, true);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
