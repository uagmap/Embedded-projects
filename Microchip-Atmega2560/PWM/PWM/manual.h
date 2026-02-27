/*
 * Project name: PWM
 * Filename: manual.h
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the header file for manual.c
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


#ifndef MANUAL_H_
#define MANUAL_H_

#include <avr/io.h>

// function prototypes
uint16_t ADC_read(void);
void ADC_init(void);
void manual_control(uint16_t adc);

// input definitions
#define start_profile_PB 0x01
#define stopPWM_PB 0x02
#define mode_switch 0x08

#define controls_input PINA

// output definitions
#define mode_LED 0x01

#define output_port PORTC

//global variables



#endif /* MANUAL_H_ */