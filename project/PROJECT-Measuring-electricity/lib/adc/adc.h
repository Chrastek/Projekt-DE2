
#ifndef ADC_H
# define ADC_H

/***********************************************************************
 * 
 * ADC library for AVR-GCC.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2023 Slavek Rylich
 * Student, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/**
 * @file 
 * @defgroup rylich_adc ADC Library <adc.h>
 * @defgroup fryza_gpio GPIO Library <gpio.h>
 * @code #include <adc.h> @endcode
 *
 * @brief ADC library for AVR-GCC.
 *
 * The library contains functions for AVR's ADC.
 *
 * @note Based on AVR Libc Reference Manual. Tested on ATmega328P 
 *       (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2.
 * @author Slavek Rylich, Student, Brno University 
 *         of Technology, Czechia
 * @copyright (c) 2023 Slavek Rylich, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>


/* Function prototypes -----------------------------------------------*/
/**
 * @brief  Select voltage reference by REFS1, REFS0.
 * @return none
 */
void ACD_select_voltage_ref(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A0(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A1(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A2(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A3(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A4(void);


/**
 * @brief  Select input channel.
 * @return none
 */
void ACD_select_channel_A5(void);


/**
 * @brief  Enable ADC module.
 * @return none
 */
void ACD_enable(void);


/**
 * @brief  Enable ADC interrupt.
 * @return none
 */
void ACD_enable_interrupt();


/**
 * @brief  Set ADC prescaler for 2.
 * @return none
 */
void ACD_set_prescaler_2();


/**
 * @brief  Set ADC prescaler for 4.
 * @return none
 */
void ACD_set_prescaler_4();


/**
 * @brief  Set ADC prescaler for 8.
 * @return none
 */
void ACD_set_prescaler_8();


/**
 * @brief  Set ADC prescaler for 16.
 * @return none
 */
void ACD_set_prescaler_16();


/**
 * @brief  Set ADC prescaler for 32.
 * @return none
 */
void ACD_set_prescaler_32();


/**
 * @brief  Set ADC prescaler for 64
 * @return none
 */
void ACD_set_prescaler_64();


/**
 * @brief  Set ADC prescaler for 128.
 * @return none
 */
void ACD_set_prescaler_128();


/**
 * @brief  Start ADC conversion.
 * @return none
 */
void ACD_start_conv();

/** @} */

#endif