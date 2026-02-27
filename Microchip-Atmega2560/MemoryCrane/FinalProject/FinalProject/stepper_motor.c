/*
 * Project name: final project
 * Filename: stepper_motor.c
 *
 * Created: 9/8/2023 8:34 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This file holds the functions for stepper motor operation modes
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * PINA.0-1				direction buttons for manual control
 * PINA.2				home switch
 * PORTC.0-3			Stepper motor outputs
 */ 

#include "stepper_motor.h"

// stepper motor coil positions arrays for different modes
uint8_t Wave[4] = {1, 2, 4, 8};
uint8_t Full[4] = {0x03, 0x06, 0x0C, 0x09};
uint8_t Half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};


//this function drives the motor for a passed mode parameter and a number of revolutions
// TREAT THIS FUNCTION AS A SAMPLE FOR DIFFERENT MODES
void Stepper_Drive (char mode, uint8_t revolutions)
{
	uint16_t steps;
	
	switch (mode)
	{
		case 'W': //Wave mode case
		{
			//512 is the number of steps for one rotation given 4 positions
			// 2048 / 4 = 512
			steps = 512 * revolutions;	
			
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 4; j++)
				{
					//switch position using loop index
					stepper_output = Wave[j]; 
					_delay_ms(3);
				}
			}
			
			break;
		}
		case 'F': //Full mode case
		{
			steps = 512 * revolutions;
			
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 4; j++)
				{
					stepper_output = Full[j];
					_delay_ms(3);
				}
			}
			
			break;
		}
		case 'H': //Half mode case
		{
			//512 is the number of steps for one rotation given 8 positions
			// 4096 / 8 = 512
			steps = 512 * revolutions;
			
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 8; j++)
				{
					stepper_output = Half[j];
					_delay_ms(3);
				}
			}
			
			break;
		}
	}
}


//this function is for manual operation mode using half step for more precision
void Stepper_Movement(char direction)
{
	if (direction == 'R') //CLOCKWISE OPERATION
	{
		//iterate up through array
		for (uint16_t j = 0; j < 8; j++)
		{
			stepper_output = Half[j];
			_delay_ms(3);
		}
	}
	
	if (direction == 'L') //CCW OPERATION
	{
		//iterate down through array
		for (uint16_t j = 8; j > 0; j--)
		{
			stepper_output = Half[j];
			_delay_ms(3);
		}
	}
}