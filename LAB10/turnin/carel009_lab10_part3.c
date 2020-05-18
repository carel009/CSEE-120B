/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #10  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1ArIXoAqOimVC7Ei5Oq-TVNbwOz7RsMln

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
TCNT1 = 0;
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

enum Three_States {START, LED1, LED2, LED3} Three_state;
unsigned long i = 0;
unsigned char threeLEDs = 0x00;

void ThreeLEDsSM()
{
	switch(Three_state)
	{
		case START:
			Three_state = LED1;
			break;
		case LED1:
			if(i < 300)
			{
			Three_state = LED1;
			i++;
			}
			else
			{
			Three_state = LED2;
			i = 0;
			}
			break;
		case LED2:
			if(i < 300)
			{
			Three_state = LED2;
			i++;
			}
			else
			{
			Three_state = LED3;
			i = 0;
			}
			break;
		case LED3:
			if(i < 300)
			{
			Three_state = LED3;
			i++;
			}
			else
			{
			Three_state = LED1;
			i = 0;
			}
			break;
		default:
			break;	
	}
	
	switch(Three_state)
	{
		case START:
			break;
		case LED1:
			threeLEDs = 0x01;
			break;
		case LED2:
			threeLEDs = 0x02;
			break;
		case LED3:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
}

enum BL_States {BL_START, ON, OFF} BL_state;
unsigned long j = 0;
unsigned char blinkingLED = 0x00;

void BlinkingLEDSM()
{
	switch(BL_state)
	{
		case BL_START:
			BL_state = ON;
			break;
		case ON:
			if(j < 1000)
			{
			BL_state = ON;
			j++;
			}
			else
			{
			BL_state = OFF;
			j = 0;
			}
			break;
		case OFF:
			if(j < 1000)
			{
			BL_state = OFF;
			j++;
			}
			else
			{
			BL_state = ON;
			j = 0;
			}
			break;
		default:
			break;
	}

	switch(BL_state)
	{
		case BL_START:
			break;
		case ON:
			blinkingLED = 0x08;
			break;
		case OFF:
			blinkingLED = 0x00;
			break;
		default:
			break;
	}
}

enum Speaker_States {Spkr_START, Spkr_WAIT, Spkr_ON, Spkr_OFF} Spkr_state;
unsigned char k = 0;
unsigned char Speaker = 0x00;

void SpeakerSM()
{
	switch(Spkr_state)
	{
		case Spkr_START:
			Spkr_state = Spkr_WAIT;
			break;
		case Spkr_WAIT:
			if((~PINA & 0x04) == 0x04)
			{
			Spkr_state = Spkr_ON;
			}
			else
			{
			Spkr_state = Spkr_WAIT;
			}
			k = 0;
			break;
		case Spkr_ON:
			if (((~PINA & 0x04) == 0x04) && (k < 2))
			{
			Spkr_state = Spkr_ON;
			k++;
			}
			else if ((~PINA & 0x04) == 0x04)
			{
			Spkr_state = Spkr_OFF;
			k = 0;
			}
			else
			{
			Spkr_state = Spkr_WAIT;
			}
			break;
		case Spkr_OFF:
			if (((~PINA & 0x04) == 0x04) && (k < 2))
			{
			Spkr_state = Spkr_OFF;
			k++;
			}
			else if ((~PINA & 0x04) == 0x04)
			{
			Spkr_state = Spkr_ON;
			k = 0;
			}
			else
			{
			Spkr_state = Spkr_WAIT;
			}
			break;
		default:
			break;
	}

	switch(Spkr_state)
	{
		case Spkr_START:
			Speaker = 0x00;
			break;
		case Spkr_WAIT:
			Speaker = 0x00;
			break;
		case Spkr_ON:
			Speaker = 0x10;
			break;
		case Spkr_OFF:
			Speaker = 0x00;
			break;
		default:
			break;
	}
}

enum Comb_States {Comb_START, OUTPUT} Comb_state;
unsigned char temp = 0x00;

void CombineLEDsSM()
{
	switch(Comb_state)
	{
		case Comb_START:
			Comb_state = OUTPUT;
			break;
		case OUTPUT:
			break;
		default:
			break;
	}

	switch(Comb_state)
	{
		case Comb_START:
			break;
		case OUTPUT:
			temp = threeLEDs | blinkingLED | Speaker;
			PORTB = temp;
			break;
		default:
			break;
	}
}

int main(void)
{
DDRA = 0x00;	PORTA = 0xFF;
DDRB = 0xFF;	PORTB = 0x00;	
TimerSet(1);
TimerOn();
Three_state = START;
BL_state = BL_START;
Spkr_state = Spkr_START;
Comb_state = Comb_START;

	while(1)
	{
	ThreeLEDsSM();
	BlinkingLEDSM();
	SpeakerSM();
	CombineLEDsSM();
	while (!TimerFlag);
	TimerFlag = 0;
	}
return 0;
}
