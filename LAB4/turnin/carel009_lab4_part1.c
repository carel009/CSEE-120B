/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, PRESS, RELEASE, PRESS2, RELEASE2} state;

void Tick()
{
	switch (state)
	{
		case Start:
			state = PRESS;
			break;
		case PRESS:
			if ((PINA & 0x01) == 0x00)
			{
			state = PRESS;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = RELEASE;
			}
			break;
		case RELEASE:
			if ((PINA & 0x01) == 0x01)
			{
			state = RELEASE;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = PRESS2;
			}
			break;
		case PRESS2:
			if ((PINA & 0x01) == 0x00)
			{
			state = PRESS2;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = RELEASE2;
			}
			break;
		case RELEASE2:
			if ((PINA & 0x01) == 0x01)
			{
			state = RELEASE2;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = PRESS;
			}
			break;
		default:
			break;
	}
	switch (state)
	{
		case Start:
			break;
		case PRESS:
			PORTB = 0x01;
			break;
		case RELEASE:
			PORTB = 0x02;
			break;
		case PRESS2:
			PORTB = 0x02;
			break;
		case RELEASE2:
			PORTB = 0x01;
			break;
		default:
			break;
	}
}
int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	PORTB = 0x00;
	state = Start;
		while (1)
		{
		Tick();
		}
	return 0;
}
