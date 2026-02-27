/*
 * Project name: PWM
 * Filename: manual.c
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This program is the manual control module for the PWM project.
 *	This module is responsible for ADC initialization and conversion.
 *	It uses both ADCL and ADCH registers that are combined in a variable for conversion result.
 *	It also has a function that is to continuously adjust the OC3A PWM output based on the ADC value.
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 *
 * PORTA.0				speed profile start PB
 * PORTA.1				stop speed profile PB
 * PORTA.3				mode switch
 * PORTF.0				manual control potentiometer
 * 
 * PORTC.0				mode LED
 * PORTE.3				output PWM
 *
 * Note: I changed the required motor timer because I was already using timer1 for my delay function
 */ 

#include "manual.h"
#include <stdio.h>


//need to initialize the ADC!!!!!!!
void ADC_init(void)
{
	ADCSRA |= ((1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); //enable ADC and set preascaler to 128 
	ADCSRB = 0x00; //not used
	ADMUX |= (1<<REFS0);	//internal 5V reference
}

uint16_t ADC_read(void)
{
	uint16_t adc_readout;
	ADMUX = (ADMUX & 0x40) | 0x00; //select channel 0
	
	ADCSRA |= (1<<ADSC);	//start conversion
	
	while((ADCSRA & (1<<ADSC)) == 1);	//wait until ADSC turns to 0 when conversion is completed
	
	//combine the output registers in a variable
	adc_readout = ADCL;
	adc_readout |= (ADCH<<8);
	
	return adc_readout;
}

void manual_control(uint16_t adc)
{
	TCCR3B |= (1<<CS31); //set prescaler to 8 to start producing a signal
	OCR3A = adc;
}