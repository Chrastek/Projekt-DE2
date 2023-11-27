#ifndef PCINT_H
# define PCINT_H

/***********************************************************************
 * 
 * PCINT (Pin Change Interrupt Request) library for AVR-GCC.
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
 * @defgroup rylich_adc PCINT Library <pcint.h>
 * @code #include <adc.h> @endcode
 *
 * @brief PCINT library for AVR-GCC.
 *
 * The library contains functions for AVR's PCINT.
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


/* Defines -----------------------------------------------------------*/
/**
 * @name  Definitions for PCINT 
 * @note  
 */

/** @brief  The low level of INT0 generates an interrupt request. */
#define PCINT0_TRIGGER_LOW EICRA &= ~((1 << ISC01) | (1 << ISC00));
/** @brief  Any logical change on INT0 generates an interrupt request. */ 
#define PCINT0_TRIGGER_TOGGLE EICRA &= ~(1 << ISC01); EICRA |= (1 << ISC00); 
/** @brief  The falling edge of INT0 generates an interrupt request. */ 
#define PCINT0_TRIGGER_FALL EICRA EICRA |= (1 << ISC01);; EICRA &= ~(1 << ISC00);
/** @brief  The rising edge of INT0 generates an interrupt request. */   
#define PCINT0_TRIGGER_RISE EICRA |= ((1 << ISC01) | (1 << ISC00)); 


/** @brief  The low level of INT1 generates an interrupt request. */
#define PCINT1_TRIGGER_LOW EICRA &= ~((1 << ISC01) | (1 << ISC00));
/** @brief  Any logical change on INT1 generates an interrupt request. */ 
#define PCINT1_TRIGGER_TOGGLE EICRA &= ~(1 << ISC01); EICRA |= (1 << ISC00); 
/** @brief  The falling edge of INT1 generates an interrupt request. */ 
#define PCINT1_TRIGGER_FALL EICRA EICRA |= (1 << ISC01);; EICRA &= ~(1 << ISC00);
/** @brief  The rising edge of INT1 generates an interrupt request. */   
#define PCINT1_TRIGGER_RISE EICRA |= ((1 << ISC01) | (1 << ISC00));   


/** @brief  INT0: External Interrupt Request Enable. */   
#define PCINT0_ENABLE  EIMSK |= (1 << INTF0);  

/** @brief  INT1: External Interrupt Request Enable. */   
#define PCINT1_ENABLE EIMSK |= (1 << INTF1);  

// Macros for PCINT23:0 pins

#endif


















