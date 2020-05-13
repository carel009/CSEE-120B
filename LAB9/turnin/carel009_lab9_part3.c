/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #9  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1_u014_m-Z8t4G1AvzP0qeH_EJXbQv8TO

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

void set_PWM(double frequency)
{
static double current_frequency;
if (frequency != current_frequency)
{

	if (!frequency) {TCCR3B &= 0x08;}
	else {TCCR3B |= 0x03;}
	if (frequency < 0.954) {OCR3A = 0xFFFF;}
	else if (frequency > 31250) {OCR3A = 0x0000;}
	else {OCR3A = (short)(8000000 / (128 * frequency)) - 1;}
	TCNT3 = 0; // resets counter
	current_frequency = frequency;
	}
}

void PWM_on()
{
TCCR3A = (1 << COM3A0);
TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
set_PWM(0);
}

void PWM_off()
{
TCCR3A = 0x00;
TCCR3B = 0x00;
}

enum States {START, INIT, NOTE1, NOTE1D, NOTE2, NOTE2D, NOTE3, NOTE3D, NOTE4, NOTE4D, NOTE5, NOTE5D, NOTE6, NOTE6D, NOTE7, NOTE7D, NOTE_1, NOTE_1D, NOTE_2, NOTE_2D, NOTE_3, NOTE_3D, NOTE_4, NOTE_4D, NOTE_5, NOTE_5D, NOTE_6, NOTE_6D, NOTE_7, HOLD} state;
unsigned long i = 0;

void Tick()
{
	switch(state)
	{
		case START:
			state = INIT;
			break;
		case INIT:
			if ((~PINA & 0x01) == 0x01)
			{
			state = NOTE1;
			}
			else
			{
			state = INIT;
			}
			break;
		case NOTE1:
			i++;
			if (i <= 20) //20
			{
			state = NOTE1;
			}
			else
			{
			state = NOTE1D;
			}
			break;
		case NOTE1D:
			i++;
			if (i <= 35) //15
			{
			state = NOTE1D;
			}
			else
			{
			state = NOTE2;
			}
			break;
		case NOTE2:
			i++;
			if (i <= 55) //20
			{
			state = NOTE2;
			}
			else
			{
			state = NOTE2D;
			}
			break;
		case NOTE2D:
			i++;
			if (i <= 85) //30
			{
			state = NOTE2D;
			}
			else
			{
			state = NOTE3;
			}
			break;
		case NOTE3:
			i++;
			if (i <= 105) //20
			{
			state = NOTE3;
			}
			else
			{
			state = NOTE3D;
			}
			break;
		case NOTE3D:
			i++;
			if (i <= 135) //30
			{
			state = NOTE3D;
			}
			else
			{
			state = NOTE4;
			}
			break;
		case NOTE4:
			i++;
			if (i <= 155) //20
			{
			state = NOTE4;
			}
			else
			{
			state = NOTE4D;
			}
			break;
		case NOTE4D:
			i++;
			if (i <= 165) //10
			{
			state = NOTE4D;
			}
			else
			{
			state = NOTE5;
			}
			break;
		case NOTE5:
			i++;
			if (i <= 185) //20
			{
			state = NOTE5;
			}
			else
			{
			state = NOTE5D;
			}
			break;
		case NOTE5D:
			i++;
			if (i <= 215) //30
			{
			state = NOTE5D;
			}
			else
			{
			state = NOTE6;
			}
			break;
		case NOTE6:
			i++;
			if (i <= 235) //20
			{
			state = NOTE6;
			}
			else
			{
			state = NOTE6D;
			}
			break;
		case NOTE6D:
			i++;
			if (i <= 290) //55
			{
			state = NOTE6D;
			}
			else
			{
			state = NOTE7;
			}
			break;
		case NOTE7:
			i++;
			if (i <= 310) //20
			{
			state = NOTE7;
			}
			else
			{
			state = NOTE7D;
			}
			break;
		case NOTE7D:
			i++;
			if (i <= 368) //58
			{
			state = NOTE7D;
			}
			else
			{
			i = 0;
			state = NOTE_1;
			}
			break;
		case NOTE_1:
			i++;
			if (i <= 20) //20
			{
			state = NOTE_1;
			}
			else
			{
			state = NOTE_1D;
			}
			break;
		case NOTE_1D:
			i++;
			if (i <= 65) //45
			{
			state = NOTE_1D;
			}
			else
			{
			state = NOTE_2;
			}
			break;
		case NOTE_2:
			i++;
			if (i <= 85) //20
			{
			state = NOTE_2;
			}
			else
			{
			state = NOTE_2D;
			}
			break;
		case NOTE_2D:
			i++;
			if (i <= 125) //40
			{
			state = NOTE_2D;
			}
			else
			{
			state = NOTE_3;
			}
			break;
		case NOTE_3:
			i++;
			if (i <= 145) //20
			{
			state = NOTE_3;
			}
			else
			{
			state = NOTE_3D;
			}
			break;
		case NOTE_3D:
			i++;
			if (i <= 195) //50
			{
			state = NOTE_3D;
			}
			else
			{
			state = NOTE_4;
			}
			break;
		case NOTE_4:
			i++;
			if (i <= 215) //20
			{
			state = NOTE_4;
			}
			else
			{
			state = NOTE_4D;
			}
			break;
		case NOTE_4D:
			i++;
			if (i <= 245) //30
			{
			state = NOTE_4D;
			}
			else
			{
			state = NOTE_5;
			}
			break;
		case NOTE_5:
			i++;
			if (i <= 261) //16
			{
			state = NOTE_5;
			}
			else
			{
			state = NOTE_5D;
			}
			break;
		case NOTE_5D:
			i++;
			if (i <= 294) //33
			{
			state = NOTE_5D;
			}
			else
			{
			state = NOTE_6;
			}
			break;
		case NOTE_6:
			i++;
			if (i <= 314) //20
			{
			state = NOTE_6;
			}
			else
			{
			state = NOTE_6D;
			}
			break;
		case NOTE_6D:
			i++;
			if (i <= 329) //15
			{
			state = NOTE_6D;
			}
			else
			{
			state = NOTE_7;
			}
			break;
		case NOTE_7:
			i++;
			if (i <= 349) //20
			{
			state = NOTE_7;
			}
			else
			{
			state = HOLD;
			}
			break;
		case HOLD:
			if ((~PINA & 0x01) == 0x01)
			{
			state = HOLD;
			}
			else
			{
			state = INIT;
			}
			break;
		default:
			break;
	}
	switch(state)
	{
		case START:
			break;
		case INIT:
			i = 0;
			set_PWM(0);
			break;
		case NOTE1:
			set_PWM(660);
			break;
		case NOTE1D:
			set_PWM(0);
			break;
		case NOTE2:
			set_PWM(660);
			break;
		case NOTE2D:
			set_PWM(0);
			break;
		case NOTE3:
			set_PWM(660);
			break;
		case NOTE3D:
			set_PWM(0);
			break;
		case NOTE4:
			set_PWM(510);
			break;
		case NOTE4D:
			set_PWM(0);
			break;
		case NOTE5:
			set_PWM(660);
			break;
		case NOTE5D:
			set_PWM(0);
			break;
		case NOTE6:
			set_PWM(770);
			break;
		case NOTE6D:
			set_PWM(0);
			break;
		case NOTE7:
			set_PWM(380);
			break;
		case NOTE7D:
			set_PWM(0);
			break;
		case NOTE_1:
			set_PWM(510);
			break;
		case NOTE_1D:
			set_PWM(0);
			break;
		case NOTE_2:
			set_PWM(380);
			break;
		case NOTE_2D:
			set_PWM(0);
			break;
		case NOTE_3:
			set_PWM(320);
			break;
		case NOTE_3D:
			set_PWM(0);
			break;
		case NOTE_4:
			set_PWM(440);
			break;
		case NOTE_4D:
			set_PWM(0);
			break;
		case NOTE_5:
			set_PWM(480);
			break;
		case NOTE_5D:
			set_PWM(0);
			break;
		case NOTE_6:
			set_PWM(450);
			break;
		case NOTE_6D:
			set_PWM(0);
			break;
		case NOTE_7:
			set_PWM(430);
			break;
		case HOLD:
			set_PWM(0);
			break;
		default:
			break;
	}
}

int main(void)
{
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
PWM_on();
TimerSet(10);
TimerOn();
state = START;
	
	while(1)
	{
	Tick();
	while (!TimerFlag);
        TimerFlag = 0;
	}
return 0;
}
