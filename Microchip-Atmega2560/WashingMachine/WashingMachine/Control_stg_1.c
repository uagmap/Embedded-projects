/*
 * Project name: Wash_MC
 * Filename: Control_stg_1.c
 *
 * Created: 9/15/2023 8:02 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This program is a washing machine controller. 
 *  In fact, all it does is waits for a start pushbutton
 *  and if the door is closed starts the washing cycle.
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

#include <avr/io.h>
#include "stepper_motor.h"
#include "stages.h"

void io_init(void);		//initialize io ports

int main(void)
{
	io_init();
	init_timer();
    while (1) 
    {
		//while the button is not pressed dont do anything
		while ((controls_input & start_PB) == 0);
		
		//if button is pressed and the door is not open start the cycle
		if ((controls_input & door_open) == 0)
		{
			//if no temp selection, don't start the cycle
			if (temperature_selection() == 'N')
				continue;
			else
				cycle();			
		}
    }
}


void io_init(void)	//function for initializing ports
{
	DDRA = 0x00;	//button input
	PORTA = 0xFF;	//pull up
	
	DDRC = 0xFF;	//stepper motor output
	PORTC = 0x00;	//off initially
	
	DDRL = 0xFF;	//stage LED output
	PORTL = 0x00;	//off initially
}
