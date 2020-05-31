/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #11  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1X8n5-MapT7WkmdgoQTHA6QBwyMhTMMsP

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "bit.h"
#include "timer.h"
#include "scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetKeypadKey() 
{
	
	PORTA = 0xEF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('1'); }
	if (GetBit(PINA,1)==0) { return('4'); }
	if (GetBit(PINA,2)==0) { return('7'); }
	if (GetBit(PINA,3)==0) { return('*'); }

	PORTA = 0xDF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('2'); }
	if (GetBit(PINA,1)==0) { return('5'); }
	if (GetBit(PINA,2)==0) { return('8'); }
	if (GetBit(PINA,3)==0) { return('0'); }

	PORTA = 0xBF;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('3'); }
	if (GetBit(PINA,1)==0) { return('6'); }
	if (GetBit(PINA,2)==0) { return('9'); }
	if (GetBit(PINA,3)==0) { return('#'); }

	PORTA = 0x7F;
	asm("nop");
	if (GetBit(PINA,0)==0) { return('A'); }
	if (GetBit(PINA,1)==0) { return('B'); }
	if (GetBit(PINA,2)==0) { return('C'); }
	if (GetBit(PINA,3)==0) { return('D'); }
		
	return('\0');
}

enum States {START, WAIT, KEYPRESS, KEYREG} state;
unsigned char x = 0x00;
unsigned char z = 0x00;
unsigned char key = 0x00;
unsigned char tmp = 0x00;

int Keypress (int state)
{
	switch(state)
	{
		case START:
			LCD_ClearScreen();
			LCD_DisplayString(1, "Congratulations!");
			state = WAIT;
			break;
		case WAIT:
			if(x == '\0')
			{
			key = x;
			state = WAIT;
			}
			else
			{
			state = KEYPRESS;
			}
			break;
		case KEYPRESS:
			state = KEYREG; 
			break;
		case KEYREG:
			if(z == '\0')
			{
			key = tmp;
			state = WAIT;
			}
			else
			{
			state = KEYREG;
			}
			break;
		default: 
			break;
	}

	switch (state)
	{
		case START:
			break;
		case WAIT:
			x = GetKeypadKey();
			break;
		case KEYPRESS:
			tmp = x;
			break;
		case KEYREG:
			z = GetKeypadKey();
			break;
		default:
			break;
	}
return state;
}

unsigned char y = 0;

int main(void)
{
DDRA = 0xF0; PORTA = 0x0F;
DDRC = 0xFF; PORTC = 0x00;
DDRD = 0xFF; PORTD = 0x00;

LCD_init();
	
unsigned long int BVal = 1;
	
unsigned long int AVal = 1;
AVal = findGCD(AVal, BVal);
	
unsigned long int GCD = AVal;
	
unsigned long int PeriodVal = BVal/GCD;
	
static task task1;
task *tasks[] = { &task1 };
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
task1.state = START;
task1.period = PeriodVal;
task1.elapsedTime = PeriodVal;
task1.TickFct = &Keypress;
	
TimerSet(GCD);
TimerOn();
	
unsigned short i;
	while(1) 
	{
		for ( i = 0; i < numTasks; i++ ) 
		{
			if ( tasks[i]->elapsedTime == tasks[i]->period )
			{
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
			}
		tasks[i]->elapsedTime += 1;
		}
		
		switch (key)
		{

			case '\0': break;
			case '1': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('1');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('1');
				}
				break;
			case '2':
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('2');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('2');
				}
				break;
			case '3': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('3');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('3');
				}
				break;
			case '4': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('4');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('4');
				}
				break;
			case '5': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('5');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('5');
				}
				break;
			case '6': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('6');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('6');
				}
				break;
			case '7': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('7');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('7');
				}
				break;
			case '8': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('8');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('8');
				}
				break;
			case '9': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('9');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('9');
				}
				break;
			case 'A': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('A');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('A');
				}
				break;
			case 'B': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('B');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('B');
				}
				break;
			case 'C': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('C');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('C');
				}
				break;
			case 'D': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('D');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('D');
				}
				break;
			case '*': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('*');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('*');
				}
				break;
			case '0': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('0');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('0');
				}
				break;
			case '#': 
				if (y >= 16)
				{
				y = 0;
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('#');
				}
				else
				{
				y++;
				LCD_Cursor (y); 
				LCD_WriteData ('#');
				}
				break;
			default: break;
			
			while (!TimerFlag);
			TimerFlag = 0;
		}
	}
return 0;
}
