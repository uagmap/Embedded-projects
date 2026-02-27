/*
 * Project name: PWM
 * Filename: main.c
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This program is the primary module for the PWM project.
 *	Its purpose is to initialize all used ports, and switch between the motor control modes.
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

//include modules
#include <avr/io.h>
#include "manual.h"
#include "speed_profile.h"
#include "my_delay.h"

void io_init(void);		//initialize io ports

int main(void)
{
	//initialize everything
	io_init();
	init_timer();
	timer3_init();
	ADC_init();
	while (1)
	{
		if ((controls_input & mode_switch) != 0)	//speed profile mode
		{
			
			//wait for start PB and while waiting blink every 500ms
			if ((controls_input & start_profile_PB) != 0)
			{
				run_speed_profile(10, 90, 8, 3);
			}
			else
			{
				output_port ^= mode_LED;
				my_delay_ms(500);
			}

		}
		else  //manual mode
		{
			while ((controls_input & mode_switch) == 0)
			{
				output_port &= ~mode_LED; //make sure LED is turned off
				manual_control(ADC_read()/2); //ADC is 10 bits and PWM is 9 bits, divide by 2 to adjust to PWM
			}
			
			//stop producing signal
			OCR3A = 0;
			TCNT3 = 0;
			TCCR3B &= ~(1 << CS31);	
		}
	}
}


void io_init(void)	//function for initializing ports
{
	DDRA = 0x00;	//port a input
	PORTA = 0xFF;	//pull up
	
	DDRE |= (1<<PE3);	//OC3A PWM output
	PORTE = 0x00;
	
	DDRC |= (1<<PC0);	//mode LED
	PORTC = 0x00;
	
	DDRF = 0x00;	//port F as input for adc
	PORTF = 0x00;	//with pull up turned off
}