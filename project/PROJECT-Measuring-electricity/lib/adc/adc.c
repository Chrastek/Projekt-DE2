
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


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: ACD_select_voltage_ref()
 * Purpose:  Select voltage reference by REFS1, REFS0.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_select_voltage_ref(void)
{
    ADMUX |= (1<<REFS0);
}


/**********************************************************************
 * Function: ACD_select_channel()
 * Purpose:  Select input channel(s).
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_select_channel_A0(void){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));}
void ACD_select_channel_A1(void){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);}
void ACD_select_channel_A2(void){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0)); ADMUX |= (1<<MUX1);}
void ACD_select_channel_A3(void){ADMUX &= ~((1<<MUX3) | (1<<MUX2)); ADMUX |= ((1<<MUX0) | (1<<MUX1));}
void ACD_select_channel_A4(void){ADMUX &= ~((1<<MUX3) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX2);}
void ACD_select_channel_A5(void){ADMUX &= ~((1<<MUX3) | (1<<MUX1)); ADMUX |= ((1<<MUX2) | (1<<MUX0));}


/**********************************************************************
 * Function: ACD_enable()
 * Purpose:  Enable ADC module.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_enable(void)
{
    ADCSRA |= (1<<ADEN);
}


/**********************************************************************
 * Function: ACD_enable_interrupt()
 * Purpose:  Enable ADC interrupt.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_enable_interrupt(void)
{
    ADCSRA |= (1<<ADIE);
}


/**********************************************************************
 * Function: ACD_set_prescaler_X()
 * Purpose:  Set ADC prescaler for 2,4,8,16,32,64 or 128.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
//Set prescaler 001 --> 2 
void ACD_set_prescaler_2(void){ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1)); ADCSRA|=(1<<ADPS0);}
//Set prescaler 010 --> 4 
void ACD_set_prescaler_4(void){ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0)); ADCSRA|=(1<<ADPS1);}
//Set prescaler 011 --> 8 
void ACD_set_prescaler_8(void){ADCSRA &= ~(1<<ADPS2); ADCSRA|=((1<<ADPS1) | (1<<ADPS0));}
//Set prescaler 100 --> 16 
void ACD_set_prescaler_16(void){ADCSRA &= ~((1<<ADPS1) | (1<<ADPS0)); ADCSRA|=(1<<ADPS2);}
//Set prescaler 101 --> 32 
void ACD_set_prescaler_32(void){ADCSRA &= ~(1<<ADPS1); ADCSRA|=((1<<ADPS2) | (1<<ADPS0));}
//Set prescaler 110 --> 64 
void ACD_set_prescaler_64(void){ADCSRA &= ~(1<<ADPS0); ADCSRA|=((1<<ADPS2) | (1<<ADPS1));}
//Set prescaler 111 --> 128 
void ACD_set_prescaler_128(void){ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));}


/**********************************************************************
 * Function: ACD_start_conv()
 * Purpose:  Start ADC conversion.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_start_conv(void)
{
    ADCSRA |= (1<<ADSC);
}
