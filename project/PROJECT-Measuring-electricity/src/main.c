/***********************************************************************
 * 
 * 
 * PROJECT MEASURING ELECTRICITY
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2023 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

#define BUTTON PB0 // Pin for button switch state
#define BUTTON1 PD2 // Pin for button of switch state
#define TOLERANCE 15 // Tolerance for ADC value of change
#define DEC 2 // The number of bits of the decimal part of the measured values

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
//#include <font.h>           // Library of defined font for Oled display
#include <oled.h>           // Oled library
#include <adc.h>           // ADC library for AVR-GCC
#include <uart.h>           // UART library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include <pcint.h>           // PCINT library for AVR-GCC



/* Global variables --------------------------------------------------*/

volatile uint8_t state = 0;

/* Global variables --------------------------------------------------*/
// Declaration of "m_data" variable with structure "Measure_data"

struct Measure_data {
   float voltage;
   float current;
   float capacitance;
   float resistance;
} m_data;



// Flag for printing new data from sensor
//volatile uint8_t new_sensor_data = 0;


/* Function definitions ----------------------------------------------*/
/**********************************************************************
* Function: Main function where the program execution begins
* Purpose:  Wait for new data from the sensor and sent them to UART.
* Returns:  none
**********************************************************************/
int main(void)
{
    //char string[2];  // String for converting numbers by itoa()

    // TWI
    twi_init();

    // UART
    uart_init(UART_BAUD_SELECT(115200, F_CPU));

     
    uart_puts("UART starting... ");
    uart_puts("done\r\n");

    

    // GPIO
    GPIO_mode_input_pullup(&DDRB, BUTTON);
    GPIO_mode_input_pullup(&DDRD, BUTTON1);

    //OLED
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    oled_charMode(DOUBLESIZE);
    //oled_puts("OLED disp.");
    //oled_puts("MULTIMETR");
    oled_puts("EL.CITY");

    oled_charMode(NORMALSIZE);

    // oled_gotoxy(x, y)
    oled_gotoxy(0, 2);
    //oled_puts("128x64, SHH1106");
    oled_puts("DE2 - projekt 2023");

    oled_gotoxy(0, 4);
    //oled_puts("BPC-DE2, Brno");
    oled_puts("Voltage:");

    // oled_drawLine(x1, y1, x2, y2, color)
    oled_drawLine(0, 25, 120, 25, WHITE);

    oled_gotoxy(0, 5);
    //oled_puts("Hum     Temp");
    oled_puts("Current:");

    oled_gotoxy(0, 6);
    oled_puts("Capacitance:");

    oled_gotoxy(0, 7);
    oled_puts("Resistance:");

    

    // // Test if sensor is ready
    // /* if (twi_test_address(SENSOR_ADR) == 0)
    //     uart_puts("I2C sensor detected\r\n");
    // else {
    //     uart_puts("[ERROR] I2C device not detected\r\n");
    //     while (1); 
    // }*/
    
    
    // /***************************************************
    //  * 
    //  * Configure ADC0 
    //  * 
    // ***************************************************/

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADC_SELECT_VOLTAGE_REF

    // Enable ADC module
    ADC_ENABLE

    // Enable conversion complete interrupt
    ADC_ENABLE_INTERRUPT

    // Set clock prescaler to 128
    ADC_SET_PRESCALER_128 

    // Configuration of 8-bit Timer/Counter0 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM0_OVF_16MS
    TIM0_OVF_ENABLE

    // Configuration of 16-bit Timer/Counter1 for Stopwatch update
    // Set the overflow prescaler to 4 ms and enable interrupt
     TIM1_OVF_1SEC
     TIM1_OVF_ENABLE

    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    //TIM2_OVF_16MS
    //TIM2_OVF_ENABLE

    

    // Configuration of External Interrupt of INT0 - PORT D PIN2
    // Set the rising edge of INT0 for an interrupt request and enable it
    INT0_TRIGGER_RISE 
    INT0_ENABLE 
    

    // Enables interrupts by setting the global interrupt mask
    sei(); 

    // oled_display();

    // Infinite loop
    while (1) {

        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */

        /* if (new_sensor_data == 1) {
            itoa(dht12.hum_int, string, 10);
            uart_puts(string);
            oled_gotoxy(0, 6);
            oled_puts(string);
            oled_puts(".");
            uart_puts(".");

            itoa(dht12.hum_dec, string, 10);
            uart_puts(string);
            oled_gotoxy(3, 6);
            oled_puts(string);
            oled_puts(" %\r\n");
            uart_puts(" %\r\n");

            itoa(dht12.temp_int, string, 10);
            uart_puts(string);
            oled_gotoxy(8, 6);
            oled_puts(string);
            oled_puts(".");
            uart_puts(".");

            itoa(dht12.temp_dec, string, 10);
            uart_puts(string);
            oled_gotoxy(11, 6);
            oled_puts(string);
            oled_puts(" °C\r\n");
            uart_puts(" °C\r\n");
            itoa(dht12.checksum, string, 10);
            uart_puts(string);
            uart_puts("\r\n");

            
            // Copy buffer to display RAM
            oled_display();

            // Do not print it again and wait for the new data
            new_sensor_data = 0; 
        }*/
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
* Function: Timer/Counter1 overflow interrupt
* Purpose:  Read temperature and humidity from DHT12, SLA = 0x5c.
**********************************************************************/
/* ISR(TIMER1_OVF_vect)
{
    // Test ACK from sensor
    twi_start();
    if (twi_write((SENSOR_ADR<<1) | TWI_WRITE) == 0) {
        // Set internal memory location
        twi_write(0x00);
        twi_stop();
        //twi_write(SENSOR_TEMP_MEM);
        //twi_stop();
        // Read data from internal memory
        twi_start();
        twi_write((SENSOR_ADR<<1) | TWI_READ);
        dht12.hum_int = twi_read(TWI_ACK);
        dht12.hum_dec = twi_read(TWI_ACK);
        dht12.temp_int = twi_read(TWI_ACK);
        dht12.temp_dec = twi_read(TWI_ACK);
        dht12.checksum = twi_read(TWI_NACK);

        new_sensor_data = 1;
    }
    twi_stop();
} */

ISR(TIMER0_OVF_vect)
{
  static uint8_t no_of_overflows = 0;

  no_of_overflows++;
  
  if(no_of_overflows >=3) {
    no_of_overflows = 0;
    // Start ADC conversion
    ADC_START_CONV
  }

}

ISR(ADC_vect)
{
    float value;
    char string[2];  // String for converted numbers by itoa()
    static uint8_t internal_state = 0;

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC*(5.0/1023);
    // Convert "value" to "string" and display it
    // itoa(value,string,10);
    // lcd_gotoxy(1, 0); lcd_puts("value:");
    // lcd_gotoxy(3, 1); lcd_puts("key:");
    // lcd_gotoxy(8, 0); lcd_puts(string);  // Put ADC value in decimal

    // itoa(value,string,16);
    // lcd_gotoxy(13,0); lcd_puts(string);  // Put ADC value in hexadecimal
    // lcd_gotoxy(8, 1); lcd_putc(value);  // Put button name here

    switch (state)
    {
    case 0:
            m_data.voltage = value;
            dtostrf(m_data.voltage,5,DEC,string);
            oled_gotoxy(13, 4);
            oled_puts(string);
            oled_puts(" V");
        break;
    case 1:
            m_data.current = value;

            dtostrf(m_data.current,5,DEC,string);
            oled_gotoxy(13, 5);
            oled_puts(string);
            oled_puts(" A");
        break;
    case 2:
            m_data.capacitance = value;

            dtostrf(m_data.capacitance,5,DEC,string);
            oled_gotoxy(13, 6);
            oled_puts(string);
            oled_puts(" F");
        break;
    case 3:
            m_data.resistance = value;

            dtostrf(m_data.resistance,5,DEC,string);
            oled_gotoxy(13, 7);
            oled_puts(string);
            oled_puts(" ");
            oled_puts("Ohm");
        break;
    
    default:
        switch (internal_state)
        {
        case 0:
                m_data.voltage = value;
                dtostrf(m_data.voltage,5,DEC,string);
                oled_gotoxy(13, 4);
                oled_puts(string);
                oled_puts(" V");
            
            internal_state = 1;
            ADC_SELECT_CHANNEL_A1
            break;
        case 1:
                m_data.current = value;

                dtostrf(m_data.current,5,DEC,string);
                oled_gotoxy(13, 5);
                oled_puts(string);
                oled_puts(" A");
            
            internal_state = 2;
            ADC_SELECT_CHANNEL_A2
            break;
        case 2:
                m_data.capacitance = value;

                dtostrf(m_data.capacitance,5,DEC,string);
                oled_gotoxy(13, 6);
                oled_puts(string);
                oled_puts(" F");
            
            internal_state = 3;
            ADC_SELECT_CHANNEL_A3
            break;
        default:
                m_data.resistance = value;

                dtostrf(m_data.resistance,5,DEC,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" ");
                oled_puts("Ohm");            
            internal_state = 0;
            ADC_SELECT_CHANNEL_A0
            break;

        }

        break;
    }

    oled_display();
}

ISR(TIMER1_OVF_vect)
{
  static uint8_t no_of_overflows = 0;
  char string [2]; 

  no_of_overflows++;
  
  if(no_of_overflows >= 2) {
    no_of_overflows = 0;

    /* uart_puts("Voltage: ");
    dtostrf(m_data.voltage,5,3,string);
    uart_puts(string);
    uart_puts(" V\r\n");

    uart_puts("Current: ");
    dtostrf(m_data.current,5,3,string);
    uart_puts(string);
    uart_puts(" A\r\n");
    itoa(state,string,10);
    uart_puts(string);
    

    uart_puts("Capacitance: ");
    dtostrf(m_data.capacitance,5,3,string);
    uart_puts(string);
    uart_puts(" F\r\n");

    uart_puts("Resistance: ");
    dtostrf(m_data.resistance,5,3,string);
    uart_puts(string);
    uart_puts(" Ohm\r\n");
 */
    uart_puts("----------------\r\n");
  }

}


ISR(INT0_vect)
{
    static uint8_t count = 0;
    // vyresit debounce
    //for(uint16_t i = 0; i<1000; i++){ ;} // delay for debounce pushbutton
    cli();
    char string [2];
    
    switch (state)
    {
    case 0:
        state = 1;
        ADC_SELECT_CHANNEL_A1
        break;
    case 1:
        state = 2;
        ADC_SELECT_CHANNEL_A2
        break;
    case 2:
        state = 3;
        ADC_SELECT_CHANNEL_A3
        break;
    case 3:
        state = 4;
        break;
    
    default:
        state = 0;
        ADC_SELECT_CHANNEL_A0
        break;
    }
    count++;
    oled_gotoxy(9, 4);
    itoa(count,string,10);
    oled_puts(string);
    sei();
}

// Tolerance 
// uart
// mereni velicin, rozsahy, jednotky,
// vzhled ? 
// dokumentace
