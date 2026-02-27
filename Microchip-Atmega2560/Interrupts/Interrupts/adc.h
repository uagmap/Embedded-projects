/*
 * Project name: PWM
 * Filename: adc.h
 *
 * Created: 10/5/2023 5:25 PM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the header file for adc.c
 *
 */ 


#ifndef MANUAL_H_
#define MANUAL_H_

#include <avr/io.h>

// function prototypes
uint16_t ADC_read(void);
void ADC_init(void);
void manual_control(uint16_t adc);
void ADC_read2(void);

// input definitions

// output definitions

//global variables


#endif /* MANUAL_H_ */