/*
 * my_delay.c
 * Created: 9/28/2023 8:37 PM
 * Author : Yaroslav Kozmenko
 *
 * Operations:
 *	custom time delay function using 16-bit Timer1
 */

#include "my_delay.h"


void init_timer(void)
{
	TCNT1 = 0;
	TCCR1A = 0;
	TCCR1B |= (1 << CS10);	//enable 8 prescaler
	TCCR1C = 0;
	OCR1A = 16000;
	
	//This added for interrupts:
	TIMSK1 |= (1 << OCIE1A);	//enable timer interrupt
}


void Delay_1ms(void)
{
	while ((TIFR1 & (1 << OCF1A)) == 0);	//wait for flag
	TCCR1B = 0;		//stop the clock
	TIFR1 |= (1 << OCF1A);	//clear the flag
	TCNT1 = 0;	//reset timer
}

//delay for given time in ms
void my_delay_ms(uint16_t time)
{
	for (uint16_t i = 0; i < time; i++)
	{
		Delay_1ms();
	}
}