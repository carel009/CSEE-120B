/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #6  Exercise #2
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

enum States {Start, LED1, LED2, LED3, LED_2, STOP, RESET} state;

void Tick()
{
	switch (state)
	{
		case Start:
			state = LED1;
			break;
		case LED1:
			if ((~PINA & 0x01) == 0x01)
			{
			state = STOP;
			}
			else
			{
			state = LED2;
			} 
			break;
		case LED2:
			if ((~PINA & 0x01) == 0x01)
			{
			state = STOP;
			}
			else
			{
			state = LED3;
			} 
			break;
		case LED3:
			if ((~PINA & 0x01) == 0x01)
			{
			state = STOP;
			}
			else
			{
			state = LED_2;
			}
			break;
		case LED_2:
			if ((~PINA & 0x01) == 0x01)
			{
			state = STOP;
			}
			else
			{
			state = LED1;
			}
			break;
		case STOP:
			if ((~PINA & 0x01) == 0x01)
			{
			state = STOP;
			}
			else
			{
			state = RESET;
			}
			break;
		case RESET:
			if ((~PINA & 0x01) == 0x01)
			{
			state = LED1;
			}
			else
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
			PORTB = 0x00;
			break;
		case LED1:
			PORTB = 0x01;
			break;
		case LED2:
			PORTB = 0x02;
			break;
		case LED3:
			PORTB = 0x04;
			break;
		case LED_2:
			PORTB = 0x02;
			break;
		case STOP:
			break;
		case RESET:
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	state = Start;
	TimerSet(37.5);
	TimerOn();
	while(1)
	{
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
return 0;
}
