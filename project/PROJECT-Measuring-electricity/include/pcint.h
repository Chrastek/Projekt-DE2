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
 * @name  Definitions for INT0, INT1 
 * @note  
 */

/** @brief  The low level of INT0 generates an interrupt request. */
#define INT0_TRIGGER_LOW EICRA &= ~((1 << ISC01) | (1 << ISC00));
/** @brief  Any logical change on INT0 generates an interrupt request. */ 
#define INT0_TRIGGER_TOGGLE EICRA &= ~(1 << ISC01); EICRA |= (1 << ISC00); 
/** @brief  The falling edge of INT0 generates an interrupt request. */ 
#define INT0_TRIGGER_FALL EICRA EICRA |= (1 << ISC01);; EICRA &= ~(1 << ISC00);
/** @brief  The rising edge of INT0 generates an interrupt request. */   
#define INT0_TRIGGER_RISE EICRA |= ((1 << ISC01) | (1 << ISC00)); 


/** @brief  The low level of INT1 generates an interrupt request. */
#define INT1_TRIGGER_LOW EICRA &= ~((1 << ISC11) | (1 << ISC10));
/** @brief  Any logical change on INT1 generates an interrupt request. */ 
#define INT1_TRIGGER_TOGGLE EICRA &= ~(1 << ISC11); EICRA |= (1 << ISC10); 
/** @brief  The falling edge of INT1 generates an interrupt request. */ 
#define INT1_TRIGGER_FALL EICRA EICRA |= (1 << ISC11);; EICRA &= ~(1 << ISC10);
/** @brief  The rising edge of INT1 generates an interrupt request. */   
#define INT1_TRIGGER_RISE EICRA |= ((1 << ISC11) | (1 << ISC10));   


/** @brief  INT0: External Interrupt Request Enable. */   
#define INT0_ENABLE  EIMSK |= (1 << INT0);  

/** @brief  INT1: External Interrupt Request Enable. */   
#define INT1_ENABLE EIMSK |= (1 << INT1);  


// reset External Interrupt Flags
/** @brief  INT0: External Interrupt Request Enable. */   
#define INT0_RESET  EIFR &= ~(1 << INTF0);  

/** @brief  INT1: External Interrupt Request Enable. */   
#define INT1_RESET EIFR &= ~(1 << INTF1); 

// Macros for PCINT23:0 pins

/** @brief  Group pins PCINT7:0 - External Interrupt Request Enable. */   
#define PCINT7_0_ENABLE PCICR |= (1 << PCIE0);

 /** @brief  Group pins PCINT15:8 - External Interrupt Request Enable. */   
#define PCINT15_8_ENABLE PCICR |= (1 << PCIE1);

 /** @brief  Group pins PCINT23:16 - External Interrupt Request Enable. */   
#define PCINT23_16_ENABLE PCICR |= (1 << PCIE2);

 /** @brief  PCINT0 triggers interrupt. */   
#define PCINT0_SET  PCMSK0 |= (1<<PCINT0);
 /** @brief  PCINT1 triggers interrupt. */   
#define PCINT1_SET  PCMSK0 |= (1<<PCINT1);
 /** @brief  PCINT2 triggers interrupt. */   
#define PCINT2_SET  PCMSK0 |= (1<<PCINT2);
 /** @brief  PCINT3 triggers interrupt. */   
#define PCINT3_SET  PCMSK0 |= (1<<PCINT3);
 /** @brief  PCINT4 triggers interrupt. */   
#define PCINT4_SET  PCMSK0 |= (1<<PCINT4);
 /** @brief  PCINT5 triggers interrupt. */   
#define PCINT5_SET  PCMSK0 |= (1<<PCINT5);
 /** @brief  PCINT6 triggers interrupt. */   
#define PCINT6_SET  PCMSK0 |= (1<<PCINT6);
 /** @brief  PCINT7 triggers interrupt. */   
#define PCINT7_SET  PCMSK0 |= (1<<PCINT7);

 /** @brief  PCINT0 do not triggers interrupt. */   
#define PCINT0_RESET  PCMSK0 &= ~(1<<PCINT0);
 /** @brief  PCINT1 do not triggers interrupt. */ 
#define PCINT1_RESET  PCMSK0 &= ~(1<<PCINT1);
 /** @brief  PCINT2 do not triggers interrupt. */  
#define PCINT2_RESET  PCMSK0 &= ~(1<<PCINT2);
 /** @brief  PCINT3 do not triggers interrupt. */  
#define PCINT3_RESET  PCMSK0 &= ~(1<<PCINT3);
 /** @brief  PCINT4 do not triggers interrupt. */  
#define PCINT4_RESET  PCMSK0 &= ~(1<<PCINT4);
 /** @brief  PCINT5 do not triggers interrupt. */   
#define PCINT5_RESET  PCMSK0 &= ~(1<<PCINT5);
 /** @brief  PCINT6 do not triggers interrupt. */  
#define PCINT6_RESET  PCMSK0 &= ~(1<<PCINT6);
 /** @brief  PCINT7 do not triggers interrupt. */  
#define PCINT7_RESET  PCMSK0 &= ~(1<<PCINT7);


#endif


















