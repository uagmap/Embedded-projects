/*
 * Project name: Interrupts
 * Filename: main.c
 *
 * Created: 10/19/2023 5:01 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This program is interrupts practice for Timer1, ADC and external INT.
 *	There are three applications of ISR here. They are described in the comments.
 *	Timer ISR is called when timer compare match happens (timer 1 ms done).
 *	ADC ISR happens when ADC conversion is done.
 *	External INT occurs whenever there is signal at assigned pins.
 *	They are defined in IO initialization.
 *	
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * PORTA.0-7			LED bar
 * PORC.7				encoder direction bit
 * PORTL				500ms blink LED
 * PORTF.0				ADC potentiometer input
 * PORTD.0				INT 0, encoder CLK
 * PORTD.1				INT 1, mode button
 */ 

//include modules
#include <avr/io.h>
#include <avr/interrupt.h>
#include "my_delay.h"
#include "adc.h"

void io_init(void);		//prototypes
void mode1(void);
void mode2(void);
void mode3(void);

//global variables
volatile uint16_t Tick = 0;
volatile uint16_t Tick2 = 0;
volatile uint8_t mode = 1;
volatile uint16_t adcValue;
volatile uint8_t knob = 0;


ISR(TIMER1_COMPA_vect) 
{
	//timer1 compare interrupt
	//reset timer and increment both tick variables
	//i am using two tick variables so that one is for the LED bar and another for separate LED
	//so that they don't interfere in mode1
	TCNT1 = 0;
	Tick++;
	Tick2++;
}


ISR(INT1_vect) 
{
	// Toggle mode between 1, 2, and 3 through external interrupt.
	//when button is pressed change mode
	mode++;
	if (mode > 3) mode = 1;
}


ISR(INT0_vect)
{
	//external interrupt, encoder clock
	//get the direction bit and increment or decrement accordingly
	if ((PINC & (1<<PC7)) != 0)
	{
		if (knob > 0) knob--;
	}
	else 
	{
		if (knob < 8) knob++;
	}
}


ISR(ADC_vect)
{
	//when ADC conversion completed, update the variable
	adcValue = ADCL;
	adcValue |= (ADCH<<8);
}


int main(void)
{
	//initialize everything
	io_init();
	ADC_init();
	init_timer();
	sei();	//global variables init
	
	while (1)
	{
		//switch between modes and blink LED simultaneously
		switch (mode) 
		{
			case 1:
				mode1();
				break;
			case 2:
				mode2();
				break;
			case 3:
				mode3();
				break;
			default:
				break;
		}
		
		if (Tick2 > 500)
		{
			PORTL ^= 0xFF;
			Tick2 = 0;
		}
	}
}


void io_init(void)	//function for initializing ports
{
	DDRA = 0xFF;	//port a out
	PORTA = 0x00;	//off
	
	DDRC = 0x00;	//encoder direction input
	PORTC = 0xFF;
			
	DDRL = 0xFF;	//blink LED output
	PORTL = 0x00;	//(im too lazy to assign specific bits :c)
	
	DDRF = 0x00;	//port F as input for adc
	PORTF = 0x00;	//with pull up turned off
	
	//external interrupts!!!
	//Set PORTD.1, 0 as input
	DDRD &= ~((1 << PD1) | (1 << PD0));
	// Enable internal pull-up resistor for PORTD.1 and 0
	PORTD |= ((1 << PD1) | (1 << PD0));
	// Enable INT1 and INT0 external interrupts
	EIMSK |= ((1 << INT1) | (1 << INT0));
	// Set INT1 to trigger on rising edge and INT0 on falling edge
	//INT1 is mode button, INT0 is encoder clock
	EICRA |= ((1 << ISC11) | (1<<ISC10) | (1<<ISC01));
}


void mode1(void)
{
	//mode 1 blink LED bar every 500 ms
	if (Tick > 500)
	{
		PORTA ^= 0xFF;
		Tick = 0;
	}
}


void mode2(void)
{
	//mode 2 display adc value
	ADC_read2();	//keep starting the conversion
	PORTA = adcValue >> 2;	//output value to LEDs shifted by 2
	
}


void mode3(void)
{
	//mode 3 display encoder
	//display shifted by the negative of encoder knob position value
	PORTA = 0xFF >> (8 - knob);
}