/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1O9whjP7vH14iU-SKaiP3PZgFDlsMxzyc

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
		if (_avr_timer_cntcurr == 0)
		{
			TimerISR();
			_avr_timer_cntcurr = _avr_timer_M;
		}
}
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States {Start, INIT, ADD, SUB, CHECK, RESET} state;
unsigned char i = 0x00;

void Tick()
{
	switch (state)
	{
		case Start:
			state = INIT;
			break;
		case INIT:
			if ((~PINA & 0x03) == 0x00)
			{
			state = INIT;
			} 
			if ((~PINA & 0x03) == 0x01)
			{
			state = ADD;
			}
			if ((~PINA & 0x03) == 0x02)
			{
			state = SUB;
			}
			if ((~PINA & 0x03) == 0x03)
			{
			state = RESET;
			}
			break;
		case ADD:
			state = CHECK;
			break;
		case SUB:
			state = CHECK;
			break;
		case CHECK:
			if ((~PINA & 0x03) == 0x00)
			{
			i = 0x00;
			state = INIT;
			} 
			if ((~PINA & 0x03) == 0x01)
			{
			i = i + 0x01;
			if (i < 0x10)
			{
			state = CHECK;
			}
			if (i == 0x10)
			{
			i = 0x00;
			state = ADD;
			}
			}
			if ((~PINA & 0x03) == 0x02)
			{
			i = i + 0x01;
			if (i < 0x10)
			{
			state = CHECK;
			}
			if (i == 0x10)
			{
			i = 0x00;
			state = SUB;
			}
			}
			if ((~PINA & 0x03) == 0x03)
			{
			i = 0x00;
			state = RESET;
			}
			break;
		case RESET:
			if ((~PINA & 0x03) == 0x00)
			{
			state = INIT;
			}
			if (((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02) || ((~PINA & 0x03) == 0x03))
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
			if (PORTB < 0x09)
			{
			PORTB = PORTB + 0x01;
			}
			if (PORTB >= 0x09)
			{
			PORTB = 0x09;
			}
			break;
		case SUB:
			if (PORTB > 0x00)
			{
			PORTB = PORTB - 0x01;
			}
			if (PORTB <= 0x00)
			{
			PORTB = 0x00;
			}
			break;
		case CHECK:
			break;
		case RESET:
			PORTB = 0x00;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	PORTB = 0x07;
	state = Start;
	TimerSet(12.5);
	TimerOn();
	while(1)
	{
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
return 0;
}
