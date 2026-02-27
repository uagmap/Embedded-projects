/*
 * Project name: Lab2Step
 * Filename: stepper_motor.h
 *
 * Created: 9/8/2023 8:29 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the header file for stepper_motor.c
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * PORTC.0-3			Stepper motor outputs
 */ 

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


// function prototypes
void Stepper_Drive(char mode, uint8_t time);

// Mode input definitions
#define Wave_Step 0x01
#define Full_Step 0x02
#define Half_Step 0x04

#define stepper_output PORTC

//global variables
extern uint8_t Wave[4];
extern uint8_t Full[4];
extern uint8_t Half[8];



#endif /* STEPPER_MOTOR_H_ */