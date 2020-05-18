/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1Yjku13ZhdOEiowsJqf_O2NgETDoGPC8u

#include <avr/io.h>
#include "io.h"
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
unsigned char cnt = 0;

void Tick()
{
	switch (state)
	{
		case Start:
			LCD_Cursor(1);
			LCD_WriteData(cnt + '0');
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
			if (cnt < 9)
			{
			cnt = cnt + 1;
			}
			if (cnt >= 9)
			{
			cnt = 9;
			}
			LCD_Cursor(1);
			LCD_WriteData(cnt + '0');
			break;
		case SUB:
			if (cnt > 0)
			{
			cnt = cnt - 1;
			}
			if (cnt <= 0)
			{
			cnt = 0;
			}
			LCD_Cursor(1);
			LCD_WriteData(cnt + '0');
			break;
		case CHECK:
			break;
		case RESET:
			cnt = 0;
			LCD_Cursor(1);
			LCD_WriteData(cnt + '0');
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
	state = Start;
	LCD_init();
	TimerSet(100);
	TimerOn();
	while(1)
	{
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
return 0;
}
