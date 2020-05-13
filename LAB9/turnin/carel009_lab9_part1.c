/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1_u014_m-Z8t4G1AvzP0qeH_EJXbQv8TO

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

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
	TCNT3 = 0;
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

enum States {START, OFF, ON} state;

void Tick()
{
	switch(state)
	{
		case START:
			state = OFF;
			break;
		case OFF:
			if(((~PINA & 0x07) == 0x01) || ((~PINA & 0x07) == 0x02) || ((~PINA & 0x07) == 0x04))
			{
			state = ON;
			}
			else
			{
			state = OFF;
			}
			break;
		case ON:
			if(((~PINA & 0x07) == 0x01) || ((~PINA & 0x07) == 0x02) || ((~PINA & 0x07) == 0x04))
			{
			state = ON;
			}
			else
			{
			state = OFF;
			}
			break;
		default:
			break;
	}
	switch(state)
	{
		case START:
			break;
		case OFF:
			set_PWM(0);
			break;
		case ON:
			if((~PINA & 0x07) == 0x01)
			{
			set_PWM(261.63);
			}
			else if((~PINA & 0x07) == 0x02)
			{
			set_PWM(293.66);
			}
			else if((~PINA & 0x07) == 0x04)
			{
			set_PWM(329.63);
			}
			break;
		default:
			break;
		
	}
}

int main(void)
{
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
state = START;
PWM_on();
	
	while(1)
	{
		Tick();
	}
return 0;
}
