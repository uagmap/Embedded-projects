/*
 * Project name: Wash_MC
 * Filename: stages.h
 *
 * Created: 9/15/2023 8:05 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the header file for stages.c
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


#ifndef STAGES_H_
#define STAGES_H_

#include <avr/io.h>
#include "my_delay.h"

// function prototypes
char temperature_selection(void);
void cycle(void);
void fill(char temperature);
void wash(void);
void drain(void);
void rinse(void);
void rinse2(void);
void done(void);

// input definitions
#define Hot 0x10
#define Warm 0x08
#define Cold 0x04
#define door_open 0x01
#define start_PB 0x80

#define controls_input PINA

// output definitions
#define done_LED 0x01
#define drain_LED 0x08
#define HotValve_LED 0x20
#define ColdValve_LED 0x10

#define controls_output PORTL


//global variables
extern char temperature;


#endif /* STAGES_H_ */