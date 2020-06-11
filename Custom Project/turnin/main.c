/*	Author: Christopher Arellano (carel009)
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Option #3 Final - Custom Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1FOEYEqOA5eHYMd_CZirsn2oVUqzsSx7w

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "bit.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetKeypadKey() 
{
	
	PORTB = 0xEF;
	asm("nop");
	if (GetBit(PINB,0)==0) { return('1'); }
	if (GetBit(PINB,1)==0) { return('4'); }
	if (GetBit(PINB,2)==0) { return('7'); }
	if (GetBit(PINB,3)==0) { return('*'); }

	PORTB = 0xDF;
	asm("nop");
	if (GetBit(PINB,0)==0) { return('2'); }
	if (GetBit(PINB,1)==0) { return('5'); }
	if (GetBit(PINB,2)==0) { return('8'); }
	if (GetBit(PINB,3)==0) { return('0'); }

	PORTB = 0xBF;
	asm("nop");
	if (GetBit(PINB,0)==0) { return('3'); }
	if (GetBit(PINB,1)==0) { return('6'); }
	if (GetBit(PINB,2)==0) { return('9'); }
	if (GetBit(PINB,3)==0) { return('#'); }

	PORTB = 0x7F;
	asm("nop");
	if (GetBit(PINB,0)==0) { return('A'); }
	if (GetBit(PINB,1)==0) { return('B'); }
	if (GetBit(PINB,2)==0) { return('C'); }
	if (GetBit(PINB,3)==0) { return('D'); }
		
	return('\0');
}

void ADC_init()
{
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

enum States {START, DISARM, NUM1A, NUM1AP, NUM2A, NUM2AP, NUM3A, NUM3AP, AWAY, NUM1DA, NUM1DAP, NUM2DA, NUM2DAP, NUM3DA, NUM3DAP, STAY, NUM1DS, NUM1DSP, NUM2DS, NUM2DSP, NUM3DS, NUM3DSP, INTRUDER, RESET, NUM1DT, NUM1DTP, NUM2DT, NUM2DTP, NUM3DT, NUM3DTP, POTINT, DISTRESS, NUM1DD, NUM1DDP, NUM2DD, NUM2DDP, NUM3DD, NUM3DDP } state;

unsigned short ADCONV;
unsigned short MAX;
unsigned short MIN;
unsigned short tmp;

unsigned char i = 0x00;
unsigned char x = 0x00;
unsigned long cnt = 0;

void Tick()
{
	switch (state)
	{
		case START:
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			break;
		case DISARM:
			if (x == '1')
			{
			state = NUM1A;
			}
			else 
			{
			state = DISARM;
			}
			break;
		case NUM1A:
			LCD_Cursor (17); 
			LCD_WriteData ('*');
			if (x == '1')
			{
			state = NUM1A;
			}
			else if (x == '\0')
			{
			state = NUM1AP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case NUM1AP:
			if (x == '\0')
			{
			state = NUM1AP;
			}
			else if (x == '2')
			{
			state = NUM2A;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case NUM2A:
			LCD_Cursor (18); 
			LCD_WriteData ('*');
			if (x == '2')
			{
			state = NUM2A;
			}
			else if (x == '\0')
			{
			state = NUM2AP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case NUM2AP:
			if (x == '\0')
			{
			state = NUM2AP;
			}
			else if (x == '3')
			{
			state = NUM3A;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case NUM3A:
			LCD_Cursor (19); 
			LCD_WriteData ('*');
			if (x == '3')
			{
			state = NUM3A;
			}
			else if (x == '\0')
			{
			state = NUM3AP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case NUM3AP:
			if (x == '\0')
			{
			state = NUM3AP;
			}
			else if (x == '#')
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			else if (x == '*')
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			break;
		case AWAY:
			ADC_init();
			if ((x != '1'))
			{
			ADCONV = ADC;
			MAX = 0x0AA;
			MIN = 0x01F;
			tmp = ((MAX - MIN) / 4);
				if ((~PIND & 0x10) == 0x10)
				{
				PORTA = 0x00;
				LCD_ClearScreen();
				LCD_DisplayString (1, "Potential       Intruder");
				state = POTINT;
				}
				else if (ADCONV <= (tmp + MIN))
				{
				PORTA = 0x42; //low light + inside lights on
				}
				else if (ADCONV <= ((2*tmp) + MIN))
				{
				PORTA = 0x26; //semi low light + outside lights on
				}
				else if (ADCONV <= ((3*tmp) + MIN))
				{
				PORTA = 0x0E; //semi bright light
				}
				else
				{
				PORTA = 0x1E; //bright light
				}
			}
			else if (x == '1')
			{
			state = NUM1DA;
			}
			else 
			{
			state = AWAY;
			} 
			break;
		case NUM1DA:
			LCD_Cursor (17); 
			LCD_WriteData ('*');
			if (x == '1')
			{
			state = NUM1DA;
			}
			else if (x == '\0')
			{
			state = NUM1DAP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case NUM1DAP:
			if (x == '\0')
			{
			state = NUM1DAP;
			}
			else if (x == '2')
			{
			state = NUM2DA;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case NUM2DA:
			LCD_Cursor (18); 
			LCD_WriteData ('*');
			if (x == '2')
			{
			state = NUM2DA;
			}
			else if (x == '\0')
			{
			state = NUM2DAP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case NUM2DAP:
			if (x == '\0')
			{
			state = NUM2DAP;
			}
			else if (x == '3')
			{
			state = NUM3DA;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case NUM3DA:
			LCD_Cursor (19); 
			LCD_WriteData ('*');
			if (x == '3')
			{
			state = NUM3DA;
			}
			else if (x == '\0')
			{
			state = NUM3DAP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case NUM3DAP:
			if (x == '\0')
			{
			state = NUM3DAP;
			}
			else if (x == '0')
			{
			PORTA = 0x00;
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Away");
			state = AWAY;
			}
			break;
		case STAY:
			if ((~PIND & 0x10) == 0x10)
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Intruder");
			state = INTRUDER;
			}
			else if (x == '1')
			{
			state = NUM1DS;
			}
			else 
			{
			state = STAY;
			} 
			break;
		case NUM1DS:
			LCD_Cursor (17); 
			LCD_WriteData ('*');
			if (x == '1')
			{
			state = NUM1DS;
			}
			else if (x == '\0')
			{
			state = NUM1DSP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case NUM1DSP:
			if (x == '\0')
			{
			state = NUM1DSP;
			}
			else if (x == '2')
			{
			state = NUM2DS;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case NUM2DS:
			LCD_Cursor (18); 
			LCD_WriteData ('*');
			if (x == '2')
			{
			state = NUM2DS;
			}
			else if (x == '\0')
			{
			state = NUM2DSP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case NUM2DSP:
			if (x == '\0')
			{
			state = NUM2DSP;
			}
			else if (x == '3')
			{
			state = NUM3DS;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case NUM3DS:
			LCD_Cursor (19); 
			LCD_WriteData ('*');
			if (x == '3')
			{
			state = NUM3DS;
			}
			else if (x == '\0')
			{
			state = NUM3DSP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case NUM3DSP:
			if (x == '\0')
			{
			state = NUM3DSP;
			}
			else if (x == '0')
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Armed - Stay");
			state = STAY;
			}
			break;
		case INTRUDER:
			i++;
			if ((i % 2) != 0)
			{
			PORTA = 0xE0;
				if ((~PIND & 0x0F) == 0x09)
				{
				PORTA = 0x12;
				LCD_ClearScreen();
				LCD_DisplayString (1, "System Reset");
				state = RESET;
				}
				else
				{
				state = INTRUDER;
				}
			}
			else
			{
			i = 0;
			PORTA = 0x60;
				if (((~PIND & 0x0F) == 0x09))
				{
				PORTA = 0x12;
				LCD_ClearScreen();
				LCD_DisplayString (1, "System Reset");
				state = RESET;
				}
				else
				{
				state = INTRUDER;
				}
			}
			break;
		case RESET:
			if (x == '1')
			{
			state = NUM1DT;
			}
			else 
			{
			state = RESET;
			} 
			break;
		case NUM1DT:
			LCD_Cursor (17); 
			LCD_WriteData ('*');
			if (x == '1')
			{
			state = NUM1DT;
			}
			else if (x == '\0')
			{
			state = NUM1DTP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case NUM1DTP:
			if (x == '\0')
			{
			state = NUM1DTP;
			}
			else if (x == '2')
			{
			state = NUM2DT;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case NUM2DT:
			LCD_Cursor (18); 
			LCD_WriteData ('*');
			if (x == '2')
			{
			state = NUM2DT;
			}
			else if (x == '\0')
			{
			state = NUM2DTP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case NUM2DTP:
			if (x == '\0')
			{
			state = NUM2DTP;
			}
			else if (x == '3')
			{
			state = NUM3DT;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case NUM3DT:
			LCD_Cursor (19); 
			LCD_WriteData ('*');
			if (x == '3')
			{
			state = NUM3DT;
			}
			else if (x == '\0')
			{
			state = NUM3DTP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case NUM3DTP:
			if (x == '\0')
			{
			state = NUM3DTP;
			}
			else if (x == '0')
			{
			PORTA = 0x00;
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "System Reset");
			state = RESET;
			}
			break;
		case POTINT:
			cnt++;
			if (cnt < 10000) //time in ms to wait until intruder mode is activated
			{
				if ((~PIND & 0x0F) == 0x00)
				{
				state = POTINT;
				}				
				else if (((~PIND & 0x0F) == 0x02) || ((~PIND & 0x0F) == 0x04))
				{
				cnt = 0;
				PORTA = 0x10;
				LCD_ClearScreen();
				LCD_DisplayString (1, "Disarmed");
				state = DISTRESS;
				}
				else if ((~PIND & 0x0F) == 0x09)
				{
				cnt = 0;
				PORTA = 0x12;
				LCD_ClearScreen();
				LCD_DisplayString (1, "System Reset");
				state = RESET;
				}
				else if (((~PIND & 0x0F) != 0x00) || ((~PIND & 0x0F) != 0x02) || ((~PIND & 0x0F) != 0x04) || ((~PIND & 0x0F) != 0x09))
				{
				cnt = 0;
				LCD_ClearScreen();
				LCD_DisplayString (1, "Intruder");
				state = INTRUDER;
				}
			}
			else
			{
			cnt = 0;
			LCD_ClearScreen();
			LCD_DisplayString (1, "Intruder");
			state = INTRUDER;
			}
			break;
		case DISTRESS:
			if (x == '1')
			{
			state = NUM1DD;
			}
			else 
			{
			state = DISTRESS;
			}
			break;
		case NUM1DD:
			LCD_Cursor (17); 
			LCD_WriteData ('*');
			if (x == '1')
			{
			state = NUM1DD;
			}
			else if (x == '\0')
			{
			state = NUM1DDP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		case NUM1DDP:
			if (x == '\0')
			{
			state = NUM1DDP;
			}
			else if (x == '2')
			{
			state = NUM2DD;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		case NUM2DD:
			LCD_Cursor (18); 
			LCD_WriteData ('*');
			if (x == '2')
			{
			state = NUM2DD;
			}
			else if (x == '\0')
			{
			state = NUM2DDP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		case NUM2DDP:
			if (x == '\0')
			{
			state = NUM2DDP;
			}
			else if (x == '3')
			{
			state = NUM3DD;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		case NUM3DD:
			LCD_Cursor (19); 
			LCD_WriteData ('*');
			if (x == '3')
			{
			state = NUM3DD;
			}
			else if (x == '\0')
			{
			state = NUM3DDP;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		case NUM3DDP:
			if (x == '\0')
			{
			state = NUM3DDP;
			}
			else if (x == '0')
			{
			PORTA = 0x00;
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISARM;
			}
			else 
			{
			LCD_ClearScreen();
			LCD_DisplayString (1, "Disarmed");
			state = DISTRESS;
			}
			break;
		default:
			break;
	}
	
	switch (state)
	{
		case START:
			break;
		case DISARM:
			x = GetKeypadKey();
			break;
		case NUM1A:
			x = GetKeypadKey();
			break;
		case NUM1AP:
			x = GetKeypadKey();
			break;
		case NUM2A:
			x = GetKeypadKey();
			break;
		case NUM2AP:
			x = GetKeypadKey();
			break;
		case NUM3A:
			x = GetKeypadKey();
			break;
		case NUM3AP:
			x = GetKeypadKey();
			break;
		case AWAY:
			x = GetKeypadKey();
			break;
		case NUM1DA:
			x = GetKeypadKey();
			break;
		case NUM1DAP:
			x = GetKeypadKey();
			break;
		case NUM2DA:
			x = GetKeypadKey();
			break;
		case NUM2DAP:
			x = GetKeypadKey();
			break;
		case NUM3DA:
			x = GetKeypadKey();
			break;
		case NUM3DAP:
			x = GetKeypadKey();
			break;
		case STAY:
			x = GetKeypadKey();
			break;
		case NUM1DS:
			x = GetKeypadKey();
			break;
		case NUM1DSP:
			x = GetKeypadKey();
			break;
		case NUM2DS:
			x = GetKeypadKey();
			break;
		case NUM2DSP:
			x = GetKeypadKey();
			break;
		case NUM3DS:
			x = GetKeypadKey();
			break;
		case NUM3DSP:
			x = GetKeypadKey();
			break;
		case INTRUDER:
			break;
		case RESET:
			x = GetKeypadKey();
			break;
		case NUM1DT:
			x = GetKeypadKey();
			break;
		case NUM1DTP:
			x = GetKeypadKey();
			break;
		case NUM2DT:
			x = GetKeypadKey();
			break;
		case NUM2DTP:
			x = GetKeypadKey();
			break;
		case NUM3DT:
			x = GetKeypadKey();
			break;
		case NUM3DTP:
			x = GetKeypadKey();
			break;
		case POTINT:
			break;
		case DISTRESS:
			x = GetKeypadKey();
			break;
		case NUM1DD:
			x = GetKeypadKey();
			break;
		case NUM1DDP:
			x = GetKeypadKey();
			break;
		case NUM2DD:
			x = GetKeypadKey();
			break;
		case NUM2DDP:
			x = GetKeypadKey();
			break;
		case NUM3DD:
			x = GetKeypadKey();
			break;
		case NUM3DDP:
			x = GetKeypadKey();
			break;
		default:
			break;
	}	
}

int main(void)
{
DDRA = 0xFE; PORTA = 0x01; //Photoresistor(PIN0), 6 LEDs(PIN1 - PIN6),  Speaker(PIN7)
DDRB = 0xF0; PORTD = 0x0F; //Keypad(ALL PINS)
DDRC = 0xFF; PORTC = 0x00; //LCD Display(ALL PINS)
DDRD = 0xE0; PORTD = 0x1F; //4 Buttons(PIN0 - PIN3), Switch(PIN4), LCD Display(PIN6 - PIN7)

state = START;
LCD_init();
TimerSet(1);
TimerOn();
	
	while (1)
	{
	Tick();
	while (!TimerFlag);
	TimerFlag = 0;
	}
return 0;
}
