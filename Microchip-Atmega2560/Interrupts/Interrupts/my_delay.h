/*
 * my_delay.c
 * Created: 9/28/2023 8:37 PM
 * Author : Yaroslav Kozmenko
 *
 * Operations:
 *	This is the header file for my_delay.c
 */


#ifndef MY_DELAY_H_
#define MY_DELAY_H_

#define F_CPU 16000000UL

#include <avr/io.h>

// function prototypes
void Delay_1ms(void);
void my_delay_ms(uint16_t time);
void init_timer(void);

#endif /* MY_DELAY_H_ */