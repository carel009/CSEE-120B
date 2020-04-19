/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, INIT, NUM, LOCK, WAIT, Y, UNLOCK} state;

void Tick()
{
	switch (state)
	{
		case Start:
			state = INIT;
			break;
		case INIT:
			if ((PINA & 0x87) == 0x04)
			{
			state = NUM;
			}
			else if ((PINA & 0x87) == 0x80)
			{
			state = LOCK;
			}
			else
			{
			state = INIT;
			}
			break;
		case NUM:
			state = WAIT;
			break;
		case LOCK:
			if ((PINA & 0x87) == 0x00)
			{
			state = INIT;
			}
			else
			{
			state = LOCK;
			}
			break;
		case WAIT:
			if ((PINA & 0x87) == 0x02)
			{
			state = Y;
			}
			else if ((PINA & 0x87) == 0x80)
			{
			state = LOCK;
			}
			else
			{
			state = INIT;
			}
			break;
		case Y:
			state = UNLOCK;
			break;
		case UNLOCK:
			if ((PINA & 0x87) == 0x00)
			{
			state = INIT;
			}
			else
			{
			state = UNLOCK;
			}
			break;
		default:
			break;
	}
	switch (state)
	{
		case Start:
			PORTC = 0x00;
			break;
		case INIT:
			PORTC = 0x01;
			break;
		case NUM:
			PORTC = 0x02;
			break;
		case LOCK:
			PORTB = 0x00;
			PORTC = 0x03;
			break;
		case WAIT:
			PORTC = 0x04;
			break;
		case Y:
			PORTB = 0x01;
			PORTC = 0x05;
			break;
		case UNLOCK:
			PORTC = 0x06;
			break;
		default:
			break;
	}
}
int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRC = 0xFF;	PORTC = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	state = Start;
		while (1)
		{
		Tick();
		}
	return 0;
}
