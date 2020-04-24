/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #5  Exercise #3
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

enum States {Start, INITR, P1, R1, P2, R2, P3, R3, P4, R4, P5, R5, P6, R6, WAITP, WAITR, PR1, RE1, PR2, RE2, PR3, RE3, PR4, RE4, PR5, RE5, PR6, RE6, INITP} state;

void Tick()
{
	switch (state)
	{
		case Start:
			state = INITR;
			break;
		case INITR:
			if ((PINA & 0x01) == 0x00)
			{
			state = INITR;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P1;
			}
			break;
		case P1:
			if ((PINA & 0x01) == 0x01)
			{
			state = P1;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R1;
			}
			break;
		case R1:
			if ((PINA & 0x01) == 0x00)
			{
			state = R1;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P2;
			}
			break;
		case P2:
			if ((PINA & 0x01) == 0x01)
			{
			state = P2;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R2;
			}
			break;
		case R2:
			if ((PINA & 0x01) == 0x00)
			{
			state = R2;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P3;
			}
			break;
		case P3:
			if ((PINA & 0x01) == 0x01)
			{
			state = P3;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R3;
			}
			break;
		case R3:
			if ((PINA & 0x01) == 0x00)
			{
			state = R3;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P4;
			}
			break;
		case P4:
			if ((PINA & 0x01) == 0x01)
			{
			state = P4;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R4;
			}
			break;
		case R4:
			if ((PINA & 0x01) == 0x00)
			{
			state = R4;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P5;
			}
			break;
		case P5:
			if ((PINA & 0x01) == 0x01)
			{
			state = P5;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R5;
			}
			break;
		case R5:
			if ((PINA & 0x01) == 0x00)
			{
			state = R5;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = P6;
			}
			break;
		case P6:
			if ((PINA & 0x01) == 0x01)
			{
			state = P6;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = R6;
			}
			break;
		case R6:
			if ((PINA & 0x01) == 0x00)
			{
			state = R6;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = WAITP;
			}
			break;
		case WAITP:
			if ((PINA & 0x01) == 0x01)
			{
			state = WAITP;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = WAITR;
			}
			break;
		case WAITR:
			if ((PINA & 0x01) == 0x00)
			{
			state = WAITR;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR1;
			}
			break;
		case PR1:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR1;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE1;
			}
			break;
		case RE1:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE1;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR2;
			}
			break;
		case PR2:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR2;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE2;
			}
			break;
		case RE2:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE2;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR3;
			}
			break;
		case PR3:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR3;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE3;
			}
			break;
		case RE3:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE3;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR4;
			}
			break;
		case PR4:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR4;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE4;
			}
			break;
		case RE4:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE4;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR5;
			}
			break;
		case PR5:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR5;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE5;
			}
			break;
		case RE5:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE5;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = PR6;
			}
			break;
		case PR6:
			if ((PINA & 0x01) == 0x01)
			{
			state = PR6;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = RE6;
			}
			break;
		case RE6:
			if ((PINA & 0x01) == 0x00)
			{
			state = RE6;
			}
			if ((PINA & 0x01) == 0x01)
			{
			state = INITP;
			}
			break;
		case INITP:
			if ((PINA & 0x01) == 0x01)
			{
			state = INITP;
			}
			if ((PINA & 0x01) == 0x00)
			{
			state = INITR;
			}
			break;
		default:
			break;
	}
	switch (state)
	{
		case Start:
			break;
		case INITR:
			PORTB = 0x00;
			break;
		case P1:
			break;
		case R1:
			PORTB = 0x01;
			break;
		case P2:
			break;
		case R2:
			PORTB = 0x03;
			break;
		case P3:
			break;
		case R3:
			PORTB = 0x07;
			break;
		case P4:
			break;
		case R4:
			PORTB = 0x0F;
			break;
		case P5:
			break;
		case R5:
			PORTB = 0x1F;
			break;
		case P6:
			break;
		case R6:
			PORTB = 0x3F;
			break;
		case WAITP:
			break;
		case WAITR:
			PORTB = 0x00;
			break;
		case PR1:
			break;
		case RE1:
			PORTB = 0x20;
			break;
		case PR2:
			break;
		case RE2:
			PORTB = 0x30;
			break;
		case PR3:
			break;
		case RE3:
			PORTB = 0x38;
			break;
		case PR4:
			break;
		case RE4:
			PORTB = 0x3C;
			break;
		case PR5:
			break;
		case RE5:
			PORTB = 0x3E;
			break;
		case PR6:
			break;
		case RE6:
			PORTB = 0x3F;
			break;
		case INITP:
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
		while (1)
		{
		Tick();
		}
	return 0;
}
