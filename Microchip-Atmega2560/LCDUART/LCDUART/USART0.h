/*
 * USART0.h
 *
 * Created: 02.11.2023 15:04:32
 *  Author: Yaroslav Kozmenko
 * 
 *	Description: This is the header file for USART.c
 */ 


#ifndef USART0_H_
#define USART0_H_

#define baud 9600
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// function prototypes
void USART_init(void);
void USART_TX(uint8_t byte);
uint8_t USART_RX(void);

// input definitions

// output definitions

//global variables


#endif /* USART0_H_ */