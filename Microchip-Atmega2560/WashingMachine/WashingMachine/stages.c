/*
 * Project name: Wash_MC
 * Filename: stepper_motor.c
 *
 * Created: 9/15/2023 8:05 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This file holds the functions for washing machine cycle stages
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * PORTC.0-3			stepper motor outputs
 * PORTA.0				door switch
 * PORTA.2-4			temperature control switches
 * PORTA.7				cycle start pushbutton
 * PORTL.0				done LED
 * PORTL.3				drain LED
 * PORTL.4				cold water valve LED
 * PORTL.5				hot water valve LED
 */ 


#include "stages.h"

char temperature;

char temperature_selection(void)
{
	//read temperature input and assign according variable
	switch (controls_input & (Hot | Warm | Cold)) {
		case Hot:
		{
			temperature = 'H';
			break;
		}
		
		case Warm:
		{
			temperature = 'W';
			break;
		}
		
		case Cold:
		{
			temperature = 'C';
			break;
		}
		
		default:
		{
			// Blink the LEDs indicating no selection
			for (int i = 0; i < 4; i++)
			{
				PORTL ^= (HotValve_LED | ColdValve_LED);  // toggle the LEDs
				my_delay_ms(250);
			}
			temperature = 'N';
			break;
		}
	}
	return temperature;
}

//main cycle sequence
void cycle(void)
{
	fill(temperature);
	wash();
	drain();
	fill(temperature);
	rinse();
	rinse2();
	done();
}

void fill(char temperature)
{
	//read the temperature variable and turn on according LEDs
	switch (temperature)
	{
		case 'H': //hot water mode case
		{
			controls_output |= HotValve_LED;
			break;
		}
		
		case 'W': //warm water mode case
		{
			controls_output |= (HotValve_LED | ColdValve_LED);
			break;
		}
		
		case 'C': //warm water mode case
		{
			controls_output |= ColdValve_LED;
			break;
		}
	}
	my_delay_ms(4000);
	controls_output &= ~(HotValve_LED | ColdValve_LED);	//turn off all valve LEDs
}


void wash(void)
{
	//motor in agitate mode for 4 seconds X2
	Stepper_Drive('A', 4);
	Stepper_Drive('A', 4);
}


void drain(void)
{
	//turn on drain LED for 4 seconds
	controls_output |= drain_LED;
	my_delay_ms(4000);
	controls_output &= ~drain_LED;
}


void rinse(void)
{
	//motor in agitate mode for 12 seconds
	Stepper_Drive('A', 12);
}

void rinse2(void)
{
	//drain and spin
	controls_output |= drain_LED;
	my_delay_ms(1000);
	//motor in spin mode for 9 seconds
	Stepper_Drive('S', 9);
	controls_output &= ~drain_LED;
}

void done(void)
{
	//turn on done LED and turn off when door is open
	while ((controls_input & door_open) == 0)
	{
		controls_output |= done_LED;
	}
	controls_output &= ~done_LED;
}