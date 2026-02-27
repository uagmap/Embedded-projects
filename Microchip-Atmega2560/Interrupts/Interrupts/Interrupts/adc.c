/*
 * Project name: interrupts
 * Filename: adc.c
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	 ADC conversion module updated for interrupts
 */ 

#include "adc.h"


//need to initialize the ADC!!!!!!!
void ADC_init(void)
{
	ADCSRA |= ((1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); //enable ADC and set preascaler to 128 
	ADCSRB = 0x00; //not used
	ADMUX |= (1<<REFS0);	//internal 5V reference
	
	//this section added for interrupt:
	ADCSRA |= (1<<ADIE);	//enable interrupt
	ADMUX = (ADMUX & 0x40) | 0x00; //select channel 0 once!!
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


void ADC_read2(void)
{
	ADCSRA |= (1<<ADSC);	//start conversion, keep starting conversion
}


void manual_control(uint16_t adc)
{
	TCCR3B |= (1<<CS31); //set prescaler to 8 to start producing a signal
	OCR3A = adc;
}