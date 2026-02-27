/*
 * FinalProject.c
 *
 * TREAT THIS AS main.c
 *
 * Created: 07.11.2023 22:26:44
 * Author : yaroslav kozmenko
 */ 

#include "manual_control.h"


int main(void)
{
	ports_init();	//initialize io
	
	while ((controls_input & (1 << home_switch)) != 0)	//at startup return to home, loop only runs once
	{
		Stepper_Movement('L');
	}
	
    while (1) 
    {
		if ((controls_input & (1 << CW_button))) //if CW button is pressed turn CW
		{
			Stepper_Movement('R');
		}
		if ((controls_input & (1 << CCW_button))) //if CCW button is pressed turn CCW
		{
			Stepper_Movement('L');
		}
    }
}


void ports_init(void)	//function for initializing ports
{
	DDRA = 0x00;	//button input
	PORTA = 0xFF;	//pull up
	
	DDRC = 0xFF;	//output to motors
	PORTC = 0x00;	//off initially
}