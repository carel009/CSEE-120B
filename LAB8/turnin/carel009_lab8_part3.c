/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=13jXOm3fTvQdYwLunP6kKvw1xTcV4A-fQ

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init()
{
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
DDRA = 0x00;	PORTA = 0xFF;
DDRB = 0xFF;	PORTB = 0x00;
ADC_init();	
	while (1)
	{
	unsigned short ADCONV = ADC;
	unsigned short MAX = 0x0BB;
		if (ADCONV >= (MAX / 2))
		{
		PORTB = 0x01;
		}
		else
		{
		PORTB = 0x00;
		}
	}
return 0;
}
