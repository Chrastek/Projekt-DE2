/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
#define LED_RED PB0   // PB0 is AVR pin where red external LED 
#define LED_GREEN_ext PD5   // PD5 is AVR pin where green external LED 
                        // is connected
//#define SHORT_DELAY 250 // Delay in milliseconds
#define SHORT_DELAY 500 // Delay in milliseconds
#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 13          // In Arduino world, PB5 is called "13"
#define PB0 8          // In Arduino world, PB5 is called "8"
#define PB0 5          // In Arduino world, PB5 is called "5"
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    //uint8_t led_green_value = 0;  // Local variable to keep LED status
    //uint8_t led_red_value = 0;  // Local variable to keep LED status
    uint8_t led_green_ext_value = 0;  // Local variable to keep LED status

    uint8_t counter = 0;
    uint8_t ones = 0b1010;
    uint8_t ones_shift = 0b1010;
    uint8_t twos = 0b1100;
    uint8_t twos_shift = 0b1100;
    uint8_t mask = 0b00000001;


    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN_ext,OUTPUT);


    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Change LED value
        if (counter < 5) {


            digitalWrite(LED_GREEN_ext, (mask & ones_shift));
            digitalWrite(LED_RED, (mask & twos_shift));

            ones_shift = ones >> counter;
            twos_shift = twos>> counter;

            // if (led_green_value == 0) {
            //     led_green_value = 1;
            //     led_red_value = 0;
            //     led_green_ext_value = 0;
            //     // Set pin to HIGH
            //     digitalWrite(LED_GREEN, HIGH);
            //     digitalWrite(LED_RED, HIGH);
            // }
            // else {
            //     led_green_value = 0;
            //     led_red_value = 1;
            //     // Clear pin to LOW
            //     digitalWrite(LED_GREEN, LOW);
            //     digitalWrite(LED_RED, LOW);
            // }
            counter++;
        }
        else {
            counter = 0;
            ones_shift = 0b1010;
            twos_shift = 0b1100;
        }
    }

    // Will never reach this
    return 0;
}