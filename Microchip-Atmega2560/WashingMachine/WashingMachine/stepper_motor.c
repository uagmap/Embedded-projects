/*
 * Project name: Lab2Step
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
 * PORTC.0-3			Stepper motor outputs
 */ 

#include "stepper_motor.h"

// stepper motor coil positions arrays for different modes
uint8_t Wave[4] = {1, 2, 4, 8};
uint8_t Full[4] = {0x03, 0x06, 0x0C, 0x09};
uint8_t Half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};


//this function drives the motor for a passed mode parameter and a number of revolutions
void Stepper_Drive (char mode, uint8_t time)
{
	uint16_t steps;
	
	switch (mode)
	{
		case 'S': //spin mode case
		{
			//convert time to seconds, divide by inter-step delay and by 4 for full mode
			steps = ((time * 1000) / 3) / 4; //total number of steps needed to spin for required time
			
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
		case 'A': //agitate mode case
		{
			// 4096 / 8 = 512 steps for one full rotation
			//need to spin 2 seconds in one direction and then 2 seconds in reversed direction
			steps = ((time * 1000) / 6) / 8; //total number of steps needed to spin for required time
			
			for (uint16_t i = 0; i < (steps / 64); i++)	//loop for total number of seconds divide by 2 second turns
			{
				for (uint16_t i = 0; i < ((2000 / 6) / 8); i++)	
				{
					for (uint16_t j = 0; j < 8; j++)
					{
						stepper_output = Half[j];
						_delay_ms(6);
					}
				}
				//change direction every 2 seconds
				for (uint16_t i = 0; i < ((2000 / 6) / 8); i++)
				{
					for (uint16_t j = 8; j > 0; j--)
					{
						stepper_output = Half[j];
						_delay_ms(6);
					}
				}
			}
			break;
		}
	}
}
