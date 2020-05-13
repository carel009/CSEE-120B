/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #8  Exercise #4
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
	unsigned short MIN = 0x03F;
	unsigned short tmp = ((MAX - MIN) / 8);
		if (ADCONV <= (tmp + MIN))
		{
		PORTB = 0x01;
		}
		else if (ADCONV <= ((2*tmp) + MIN))
		{
		PORTB = 0x03;
		}
		else if (ADCONV <= ((3*tmp) + MIN))
		{
		PORTB = 0x07;
		}
		else if (ADCONV <= ((4*tmp) + MIN))
		{
		PORTB = 0x0F;
		}
		else if (ADCONV <= ((5*tmp) + MIN))
		{
		PORTB = 0x1F;
		}
		else if (ADCONV <= ((6*tmp) + MIN))
		{
		PORTB = 0x3F;
		}
		else if (ADCONV <= ((7*tmp) + MIN))
		{
		PORTB = 0x7F;
		}
		else
		{
		PORTB = 0xFF;
		}
	}
return 0;
}
