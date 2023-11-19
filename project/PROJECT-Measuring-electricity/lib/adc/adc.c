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
void ACD_select_voltage_ref()
{
    ADMUX |= (1<<REFS0);
}


/**********************************************************************
 * Function: ACD_select_channel()
 * Purpose:  Select input channel(s).
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_select_channel_A0(){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));}
void ACD_select_channel_A1(){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);}
void ACD_select_channel_A2(){ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0)); ADMUX |= (1<<MUX1);}
void ACD_select_channel_A3(){ADMUX &= ~((1<<MUX3) | (1<<MUX2)); ADMUX |= ((1<<MUX0) | (1<<MUX1));}
void ACD_select_channel_A4(){ADMUX &= ~((1<<MUX3) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX2);}
void ACD_select_channel_A5(){ADMUX &= ~((1<<MUX3) | (1<<MUX1)); ADMUX |= ((1<<MUX2) | (1<<MUX0));}


/**********************************************************************
 * Function: ACD_enable()
 * Purpose:  Enable ADC module.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_enable()
{
    ADCSRA |= (1<<ADEN);
}


/**********************************************************************
 * Function: ACD_enable_interrupt()
 * Purpose:  Enable ADC interrupt.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_enable_interrupt()
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
void ACD_set_prescaler_2(){ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1)); ADCSRA|=(1<<ADPS0);}
//Set prescaler 010 --> 4 
void ACD_set_prescaler_4(){ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0)); ADCSRA|=(1<<ADPS1);}
//Set prescaler 011 --> 8 
void ACD_set_prescaler_8(){ADCSRA &= ~(1<<ADPS2); ADCSRA|=((1<<ADPS1) | (1<<ADPS0));}
//Set prescaler 100 --> 16 
void ACD_set_prescaler_16(){ADCSRA &= ~((1<<ADPS1) | (1<<ADPS0)); ADCSRA|=(1<<ADPS2);}
//Set prescaler 101 --> 32 
void ACD_set_prescaler_32(){ADCSRA &= ~(1<<ADPS1); ADCSRA|=((1<<ADPS2) | (1<<ADPS0));}
//Set prescaler 110 --> 64 
void ACD_set_prescaler_64(){ADCSRA &= ~(1<<ADPS0); ADCSRA|=((1<<ADPS2) | (1<<ADPS1));}
//Set prescaler 111 --> 128 
void ACD_set_prescaler_128(){ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));}


/**********************************************************************
 * Function: ACD_start_conv()
 * Purpose:  Start ADC conversion.
 * Input(s): none
 * Returns:  none
 **********************************************************************/
void ACD_start_conv()
{
    ADCSRA |= (1<<ADSC);
}
