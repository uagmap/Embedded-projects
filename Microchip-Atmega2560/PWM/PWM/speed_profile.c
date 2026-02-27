/*
 * Project name: PWM
 * Filename: speed_profile.c
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the speed profile module. It initializes the timer for PWM output,
 *	as well as contains a formula for the speed profile.
 *	The timer mode used is 9-bit fast pwm because it was perfectly suitable for the given frequency.
 *	The equation calculates for the duty cycle change per step, and adjusts it to the OCR value.
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

#include "speed_profile.h"

uint16_t deltaDC;

void timer3_init(void)
{
	TCNT3 = 0; //not used
	TCCR3A |= ((1<<WGM31) | (1<<COM3A1));	//mode 6, clear on match (mode 2)
	TCCR3B |= (1<<WGM32);	//should be set to a prescaler to start the timer (1<<CS31)
	TCCR3C = 0;	//not used
	OCR3A = 0;	//controls the duty cycle, set in the function
}
void run_speed_profile(uint8_t startDC, uint8_t endDC, uint16_t steps, uint16_t time_S)
{
	while ((controls_input & stopPWM_PB) == 0) //while stop PB is not pressed do the thing
	{
		//need to convert given DC to OCR3A
		deltaDC = (endDC-startDC)/steps;	//variable for change in DC per step
		TCCR3B |= (1<<CS31); //set prescaler to 8 to start producing a signal
		OCR3A = ((startDC*512)/100); //start OCR
		
		//run for number of steps
		for (int i = 0; i <= steps; i++)
		{
			if(controls_input & stopPWM_PB) break; //run until stopped
			OCR3A = (((startDC + deltaDC * i) * 512) / 100); //start OCR plus increment
			
			my_delay_ms((time_S*1000)/steps); //the sum of delays should make the time_S parameter
			
		}
	}
	//stop producing signal
	OCR3A = 0;
	TCNT3 = 0;
	TCCR3B &= ~(1 << CS31);	
}