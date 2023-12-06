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

#define TEST_PIN PD4

#define BUTTON PB0 // Pin for button switch state
#define BUTTON1 PD2 // Pin for button of switch state
#define CHARGE_PIN PD5 // Pin for charge measuring capacitor - Arduino PIN 8
#define DISCHARGE_PIN PD6 // Pin for discharge measuring capacitor - Arduino PIN 9
#define TOLERANCE 15 // Tolerance for ADC value of change
#define DEC 2 // The number of bits of the decimal part of the measured values
#define REF_RESISTOR 1000
#define REF_RESISTOR_CAP 10000.0F
#define TIMER2_LENGTH 0.001
#define REF_VOLTAGE 5.0

#define MVPERAMP 0.185
#define ACSOFTSET 2500


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

volatile uint8_t state = 0;         // state machine

volatile uint8_t butt_down = 0;     // buttun down flag


/* Global variables --------------------------------------------------*/
// Declaration of "m_data" variable with structure "Measure_data"

struct Measure_data {
   float voltage;
   float current;
   float capacitance;
   float capacit_value;
   float resistance;
} m_data;


void Clear_display_values(void)
{
    oled_gotoxy(9, 4);
    oled_puts("     ");
    oled_gotoxy(9, 5);
    oled_puts("       ");
    oled_gotoxy(13, 4);
    oled_puts("        ");
    oled_gotoxy(13, 5);
    oled_puts("        ");
    oled_gotoxy(13, 6);
    oled_puts("        ");
    oled_gotoxy(13, 7);
    oled_puts("        ");
}

void Clear_display_capacit_time(void)
{
    oled_gotoxy(9, 5);
    oled_puts("    ");
}



/* Function definitions ----------------------------------------------*/
/**********************************************************************
* Function: Main function where the program execution begins
* Purpose:  Wait for new data from the sensor and sent them to UART.
* Returns:  none
**********************************************************************/
int main(void)
{
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
    TIM0_OVF_1MS
    TIM0_OVF_ENABLE

    // Configuration of 16-bit Timer/Counter1 for Stopwatch update
    // Set the overflow prescaler to 4 ms and enable interrupt
    TIM1_OVF_33MS
    TIM1_OVF_ENABLE
    

    // Configuration of External Interrupt of INT0 - PORT D PIN2
    // Set the rising edge of INT0 for an interrupt request and enable it
    INT0_TRIGGER_RISE 
    INT0_ENABLE 
    

    // Enables interrupts by setting the global interrupt mask
    sei(); 

    // Infinite loop
    while (1) {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
* Function: Timer/Counter1 overflow interrupt
* Purpose:  Read temperature and humidity from DHT12, SLA = 0x5c.
**********************************************************************/

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



ISR(TIMER1_OVF_vect)        // debouncer
{
  static uint8_t no_of_overflows = 0;

  no_of_overflows++;
  
  
   if(no_of_overflows >= 12) 
   {
        if (butt_down > 0)
        {

            //Clear_display_capacit_time();

            cli();
            no_of_overflows = 0;  
            butt_down = 0;
            

            switch (state)
            {
            case 0:
                state++;
                ADC_SELECT_CHANNEL_A1
                break;
            case 1:

                // Configuration of 8-bit Timer/Counter0 for Stopwatch update
                // Set the overflow prescaler to 16 ms and enable interrupt
                TIM2_OVF_1MS
                TIM2_OVF_ENABLE

                state++;
                ADC_SELECT_CHANNEL_A2
                break;
            case 2:

                // Disable TIMER2 interrupt     
                TIM2_OVF_DISABLE

                state++;
                ADC_SELECT_CHANNEL_A3
                break;
            case 3:

                // Configuration of 8-bit Timer/Counter2 for Stopwatch update
                // Set the overflow prescaler to 1 ms and enable interrupt
                TIM2_OVF_1MS
                TIM2_OVF_ENABLE

                state++;       // no select channel because it is automatic mode
                break;
            
            default:

                // Disable TIMER2 interrupt     
                TIM2_OVF_DISABLE

                state = 0;
                ADC_SELECT_CHANNEL_A0
                break;
            }
            Clear_display_values();

            sei();
        }
   }

}

ISR(TIMER2_OVF_vect)
{
     static uint32_t capacit_time = 0;       // big number for sufficient time space
    static uint8_t measure_run = 0;
    static uint8_t state_capacit = 0;
    char string[2];


    if (measure_run)
    {
        oled_gotoxy(9, 5);
        itoa(capacit_time,string,10);
        oled_puts(string); 
        capacit_time++;
        
        if (m_data.capacit_value > 647)
        {
            measure_run = 0;

            m_data.capacitance = (((float)(capacit_time*5.1)))-253.73;
            //m_data.capacitance = (((float)(capacit_time*TIMER2_LENGTH))/REF_RESISTOR_CAP)*39.1*1000000; // microFarads
            //m_data.capacitance = (((float)capacit_time/REF_RESISTOR_CAP)*6563.7)-208.5; // microFarads  for 16ms
            state_capacit++;
            GPIO_write_low(&PORTD, CHARGE_PIN);
            Clear_display_capacit_time();
        }
    }
    else
    {
        switch (state_capacit)
        {
        case 0: // discharge
            GPIO_mode_output(&DDRD,DISCHARGE_PIN);
            GPIO_write_low(&PORTD, DISCHARGE_PIN);
            if (m_data.capacit_value > 0)
            {
                 ; // discharging capacitor
            }
            else
            {
                GPIO_mode_input_pullup(&DDRD, DISCHARGE_PIN); 
                 state_capacit = 1;
            }
            
            break;
        case 1: // charge
            GPIO_mode_output(&DDRD, CHARGE_PIN);
            GPIO_write_high(&PORTD, CHARGE_PIN);
            measure_run = 1;
            capacit_time = 0; 
            break;
        
        default:
            state_capacit = 0;
            break;
        }  

    
    }


}

ISR(INT0_vect)
{
    butt_down++;
}

ISR(ADC_vect)
{
    float value;
    char string[2];  // String for converted numbers by itoa()
    static uint8_t internal_state = 0;

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC*(REF_VOLTAGE/1023);

    switch (state)
    {
    case 0:
            if(value < 1.0)
                {
                m_data.voltage = value*1000;
                dtostrf(m_data.voltage,5,0,string);
                oled_gotoxy(13, 4);
                oled_puts(string);
                oled_puts(" mV");
                }
                else
                {
                    m_data.voltage = value;
                dtostrf(m_data.voltage,5,DEC,string);
                oled_gotoxy(14, 4);
                oled_puts(string);
                oled_puts(" V");
                }
        break;
    case 1:
<<<<<<< HEAD
            m_data.current = (ACSOFTSET - (value*1000) )/MVPERAMP;
=======
            m_data.current = (ACSOFTSET - (value*1000))/MVPERAMP;
>>>>>>> 94863d0c48045511c722fba0ffa50ef98b92467a

            dtostrf(m_data.current,5,DEC,string);
            oled_gotoxy(13, 5);
            oled_puts(string);
            oled_puts(" mA");
        break;
    case 2:
            m_data.capacit_value = ADC;

            dtostrf(m_data.capacitance,5,0,string);
            oled_gotoxy(13, 6);
            oled_puts(string);
            oled_puts(" uF");
        break;
    case 3:
            m_data.resistance = ((REF_RESISTOR*REF_VOLTAGE)/value)-REF_RESISTOR;
            
            if (m_data.resistance < 1000)
            {
                dtostrf(m_data.resistance,5,DEC-1,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" R");
            }
            if (m_data.resistance >= 1000 && m_data.resistance/1000 < 1000 )
            {
                dtostrf(m_data.resistance/1000,5,DEC,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" k");
            }
            if (m_data.resistance/1000 >= 1000)
            {
                dtostrf(m_data.resistance/1000000,5,DEC,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" M");
            }
            
        break;
    
    default:
        switch (internal_state)
        {
        case 0:
                if(value < 1.0)
                {
                m_data.voltage = value*1000;
                dtostrf(m_data.voltage,5,0,string);
                oled_gotoxy(13, 4);
                oled_puts(string);
                oled_puts(" mV");
                }
                else
                {
                    m_data.voltage = value;
                dtostrf(m_data.voltage,5,DEC,string);
                oled_gotoxy(14, 4);
                oled_puts(string);
                oled_puts(" V");
                }
            
            internal_state = 1;
            ADC_SELECT_CHANNEL_A1
            break;
        case 1:
                m_data.current = (ACSOFTSET - (value*1000) )/MVPERAMP;

                dtostrf(m_data.current,5,DEC,string);
                oled_gotoxy(13, 5);
                oled_puts(string);
                oled_puts(" mA");
            
            internal_state = 2;
            ADC_SELECT_CHANNEL_A2
            break;
        case 2:
            m_data.capacit_value = ADC;

            dtostrf(m_data.capacitance,5,0,string);
            oled_gotoxy(13, 6);
            oled_puts(string);
            oled_puts(" uF");
            internal_state = 3;
            ADC_SELECT_CHANNEL_A3
            break;
            
        default:
            m_data.resistance = ((REF_RESISTOR*REF_VOLTAGE)/value)-REF_RESISTOR;
            
            if (m_data.resistance < 1000)
            {
                dtostrf(m_data.resistance,5,DEC-1,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" R");
            }
            else if (m_data.resistance >= 1000 && m_data.resistance/1000 < 1000 )
            {
                dtostrf(m_data.resistance/1000,5,DEC,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" k");
            }
            else
            {
                dtostrf(m_data.resistance,5,DEC,string);
                oled_gotoxy(13, 7);
                oled_puts(string);
                oled_puts(" M");
            }        
            internal_state = 0;
            ADC_SELECT_CHANNEL_A0
            break;

        }
        break;
    }

    oled_display();
}


// dodelat capacitanci dopsat problem
// 
// vycistit kód
// dokumentace
