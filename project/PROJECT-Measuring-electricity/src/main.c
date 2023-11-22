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


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
//#include <font.h>           // Library of defined font for Oled display
#include <oled.h>           // Oled library
#include <adc.h>           // ADC library for AVR-GCC



/* Global variables --------------------------------------------------*/
/* Global variables --------------------------------------------------*/
// Declaration of "dht12" variable with structure "DHT_values_structure"

/* struct DHT_values_structure {
   uint8_t hum_int;
   uint8_t hum_dec;
   uint8_t temp_int;
   uint8_t temp_dec;
   uint8_t checksum;
} dht12; */

struct Measure_data {
   uint8_t voltage;
   uint8_t current;
   uint8_t capacitance;
   uint8_t resistance;
} m_data;

// Flag for printing new data from sensor
//volatile uint8_t new_sensor_data = 0;


// Slave and internal addresses of temperature/humidity sensor DHT12
#define SENSOR_ADR 0x5c
#define SENSOR_HUM_MEM 0
#define SENSOR_TEMP_MEM 2
#define SENSOR_CHECKSUM 4


/* Function definitions ----------------------------------------------*/
/**********************************************************************
* Function: Main function where the program execution begins
* Purpose:  Wait for new data from the sensor and sent them to UART.
* Returns:  none
**********************************************************************/
int main(void)
{
    char string[2];  // String for converting numbers by itoa()

    // TWI
    twi_init();

    // UART
    uart_init(UART_BAUD_SELECT(9600, F_CPU));


    //OLED
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    oled_charMode(DOUBLESIZE);
    //oled_puts("OLED disp.");
    oled_puts("MULTIMETR");

    oled_charMode(NORMALSIZE);

    // oled_gotoxy(x, y)
    oled_gotoxy(0, 2);
    //oled_puts("128x64, SHH1106");
    oled_puts("DE2 - projekt 2023");

    oled_gotoxy(0, 3);
    //oled_puts("BPC-DE2, Brno");
    oled_puts("Voltage:");

    // oled_drawLine(x1, y1, x2, y2, color)
    oled_drawLine(0, 25, 120, 25, WHITE);

    oled_gotoxy(0, 4);
    //oled_puts("Hum     Temp");
    oled_puts("Current:");

    oled_gotoxy(0, 5);
    oled_puts("Capacitance:");

    oled_gotoxy(0, 6);
    oled_puts("Resistance:");

    

    // Test if sensor is ready
    if (twi_test_address(SENSOR_ADR) == 0)
        uart_puts("I2C sensor detected\r\n");
    else {
        uart_puts("[ERROR] I2C device not detected\r\n");
        while (1);
    }
    
    
    /***************************************************
     * 
     * Configure ADC0 
     * 
    ***************************************************/

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX |= (1<<REFS0);
    ACD_select_voltage_ref();

    // Select input channel ADC0 (voltage divider pin), 0001
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);

    // Enable ADC module
    ADCSRA |= (1<<ADEN);
    ACD_enable();


    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);
    ACD_enable_interrupt()

    // Set clock prescaler to 128
    ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));
    ACD_set_prescaler_128(); 

    // Configuration of 8-bit Timer/Counter0 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM0_OVF_16MS
    TIM0_OVF_ENABLE

    // Configuration of 16-bit Timer/Counter1 for Stopwatch update
    // Set the overflow prescaler to 4 ms and enable interrupt
    TIM1_OVF_4MS
    TIM1_OVF_ENABLE

    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    TIM2_OVF_16MS
    TIM2_OVF_ENABLE

    // Enables interrupts by setting the global interrupt mask
    sei();  

    oled_display();

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

ISR(TIMER1_OVF_vect)
{
  static uint8_t no_of_overflows = 0;

  no_of_overflows++;
  
  if(no_of_overflows >=3) {
    // Start ADC conversion
    ACD_start_conv();
  }

}

ISR(ADC_vect)
{
    static uint8_t channel = 0; //statemachine
    uint16_t value;
    char string[4];  // String for converted numbers by itoa()

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC;
    // Convert "value" to "string" and display it
    // itoa(value,string,10);
    // lcd_gotoxy(1, 0); lcd_puts("value:");
    // lcd_gotoxy(3, 1); lcd_puts("key:");
    // lcd_gotoxy(8, 0); lcd_puts(string);  // Put ADC value in decimal

    // itoa(value,string,16);
    // lcd_gotoxy(13,0); lcd_puts(string);  // Put ADC value in hexadecimal
    // lcd_gotoxy(8, 1); lcd_putc(value);  // Put button name here

    switch (channel)
    {
    case 0:
        m_data.voltage = value;

        itoa(m_data.voltage, string, 10);
        uart_puts(string);
        oled_gotoxy(14, 3);
        oled_puts(string);
        //oled_puts(".");
        //uart_puts(".");

        channel = 1;
        ACD_select_channel_A1();
        break;
    case 1:
        m_data.current = value;

        itoa(m_data.voltage, string, 10);
        uart_puts(string);
        oled_gotoxy(14, 4);
        oled_puts(string);

        channel = 2;
        ACD_select_channel_A2();
        break;
    case 2:
        m_data.capacitance = value;

        itoa(m_data.voltage, string, 10);
        uart_puts(string);
        oled_gotoxy(14, 5);
        oled_puts(string);

        channel = 3;
        ACD_select_channel_A3();
        break;
    
    default:
        m_data.resistance = value;

        itoa(m_data.voltage, string, 10);
        uart_puts(string);
        oled_gotoxy(14, 6);
        oled_puts(string);

        channel = 0;
        ACD_select_channel_A0();
        break;
    }

}