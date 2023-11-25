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
 * Function: ADC_select_voltage_ref()
 * Purpose:  Select voltage reference by REFS1, REFS0.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_SELECT_VOLTAGE_REF ADMUX |= (1<<REFS0);

/**********************************************************************
 * Function: ADC_select_channel()
 * Purpose:  Select input channel(s).
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_SELECT_CHANNEL_A0 ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
#define ADC_SELECT_CHANNEL_A1 ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);
#define ADC_SELECT_CHANNEL_A2 ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0)); ADMUX |= (1<<MUX1);
#define ADC_SELECT_CHANNEL_A3 ADMUX &= ~((1<<MUX3) | (1<<MUX2)); ADMUX |= ((1<<MUX0) | (1<<MUX1));
#define ADC_SELECT_CHANNEL_A4 ADMUX &= ~((1<<MUX3) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX2);
#define ADC_SELECT_CHANNEL_A5 ADMUX &= ~((1<<MUX3) | (1<<MUX1)); ADMUX |= ((1<<MUX2) | (1<<MUX0));


/**********************************************************************
 * Function: ADC_enable()
 * Purpose:  Enable ADC module.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_ENABLE      ADCSRA |= (1<<ADEN);


/**********************************************************************
 * Function: ADC_disable()
 * Purpose: Disable ADC module.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_DISABLE      ADCSRA &= ~(1<<ADEN);

/**********************************************************************
 * Function: ADC_enable_interrupt()
 * Purpose:  Enable ADC interrupt.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_ENABLE_INTERRUPT        ADCSRA |= (1<<ADIE);



/**********************************************************************
 * Function: ADC_set_prescaler_X()
 * Purpose:  Set ADC prescaler for 2,4,8,16,32,64 or 128.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
//Set prescaler 001 --> 2 
#define ADC_SET_PRESCALER_2        ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1)); ADCSRA|=(1<<ADPS0);
//Set prescaler 010 --> 4 
#define ADC_SET_PRESCALER_4       ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0)); ADCSRA|=(1<<ADPS1);
//Set prescaler 011 --> 8 
#define ADC_SET_PRESCALER_8         ADCSRA &= ~(1<<ADPS2); ADCSRA|=((1<<ADPS1) | (1<<ADPS0));
//Set prescaler 100 --> 16 
#define ADC_SET_PRESCALER_16        ADCSRA &= ~((1<<ADPS1) | (1<<ADPS0)); ADCSRA|=(1<<ADPS2);
//Set prescaler 101 --> 32 
#define ADC_SET_PRESCALER_32        ADCSRA &= ~(1<<ADPS1); ADCSRA|=((1<<ADPS2) | (1<<ADPS0));
//Set prescaler 110 --> 64 
#define ADC_SET_PRESCALER_64        ADCSRA &= ~(1<<ADPS0); ADCSRA|=((1<<ADPS2) | (1<<ADPS1));
//Set prescaler 111 --> 128 
#define ADC_SET_PRESCALER_128       ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));


/**********************************************************************
 * Function: ADC_start_conv()
 * Purpose:  Start ADC conversion.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
#define ADC_START_CONV   ADCSRA |= (1<<ADSC);  

