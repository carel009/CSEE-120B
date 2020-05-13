/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #9  Exercise #2
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

enum States{START, OFF, HOLD1, ON, HOLD2, INC, DEC, WAIT} state;
double array[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i = 0x00;
const unsigned char max = 0x07;
const unsigned char min = 0x00;
double temp = 0;

void Tick()
{
	switch(state)
	{
		case START:
			state = OFF;
			break;
		case OFF:
			if((~PINA & 0x07) == 0x04)
			{
			state = HOLD1;
			}
			else
			{
			state = OFF;
			}
			break;
		case HOLD1:
			if((~PINA & 0x07) == 0x04)
			{
			state = HOLD1;
			}
			else
			{
			state = ON;
			}
			break;
		case ON:
			if((~PINA & 0x07) == 0x01)
			{
			state = INC;
			}
			else if((~PINA & 0x07) == 0x02)
			{
			state = DEC;
			}
			else if((~PINA & 0x07) == 0x04)
			{
			state = HOLD2;
			}
			else
			{
			state = ON;
			}
			break;
		case HOLD2:
			if((~PINA & 0x07) == 0x04)
			{
			state = HOLD2;
			}
			else
			{
			state = OFF;
			}
			break;
		case INC:
			temp = array[i];
			state = WAIT;
			break;
		case DEC:
			temp = array[i];
			state = WAIT;
			break;
		case WAIT:
			if((~PINA & 0x07) == 0x00)
			{
			state = ON;
			}
			else
			{
			state = WAIT;
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
		case HOLD1:
			break;
		case ON:
			temp = array[i];
			set_PWM(temp);
			break;
		case HOLD2:
			break;
		case INC:
			if((i + 1) > max)
			{
			i = max;
			}
			else
			{
			i = i + 1;
			}
			break;
		case DEC:
			if((i - 1) < min)
			{
			i = min;
			}
			else
			{
			i = i - 1;
			}
			break;
		case WAIT:
			temp = array[i];
			set_PWM(temp);
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
