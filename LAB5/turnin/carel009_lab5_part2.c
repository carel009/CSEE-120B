/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1oE9gniHYFpaFoTQG5NnLuzv0UOcLo92K

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, INIT, ADD, SUB, RESET, WAIT} state;

void Tick()
{
	switch (state)
	{
		case Start:
			state = INIT;
			break;
		case INIT:
			if ((PINA & 0x03) == 0x03)
			{
			state = INIT;
			}
			if ((PINA & 0x03) == 0x02)
			{
			state = ADD;
			}
			if ((PINA & 0x03) == 0x01)
			{
			state = SUB;
			}
			if ((PINA & 0x03) == 0x00)
			{
			state = RESET;
			}
			break;
		case ADD:
			state = WAIT;
			break;
		case SUB:
			state = WAIT;
			break;
		case RESET:
			if ((PINA & 0x03) == 0x03)
			{
			state = INIT;
			}
			if (((PINA & 0x03) == 0x02) || ((PINA & 0x03) == 0x01) || ((PINA & 0x03) == 0x00))
			{
			state = RESET;
			}
			break;
		case WAIT:
			if ((PINA & 0x03) == 0x03)
			{
			state = INIT;
			}
			if (((PINA & 0x03) == 0x02) || ((PINA & 0x03) == 0x01))
			{
			state = WAIT;
			}
			if ((PINA & 0x03) == 0x00)
			{
			state = RESET;
			}
			break;
		default:
			break;
	}
	switch (state)
	{
		case Start:
			break;
		case INIT:
			break;
		case ADD:
			if (PORTC < 0x09)
			{
			PORTC = PORTC + 0x01;
			}
			if (PORTC >= 0x09)
			{
			PORTC = 0x09;
			}
			break;
		case SUB:
			if (PORTC <= 0x00)
			{
			PORTC = 0x00;
			}
			if (PORTC > 0x00)
			{
			PORTC = PORTC - 0x01;
			}
			break;
		case RESET:
			PORTC = 0x00;
			break;
		case WAIT:
			break;
		default:
			break;
	}
}
int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	PORTC = 0x00;
	state = Start;
		while (1)
		{
		Tick();
		}
	return 0;
}
