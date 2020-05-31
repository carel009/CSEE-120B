/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=1X8n5-MapT7WkmdgoQTHA6QBwyMhTMMsP

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "timer.h"
#include "scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {START, WAIT, MSG1, MSG2, MSG3} state;
unsigned char x = 0;

int Message(int state) 
{
	switch(state)
	{
		case START:
			state = WAIT;
			break;
		case WAIT:
			if ((~PIND & 0x01) == 0x01) 
			{
			state = MSG1;
			}
			else
			{
			state = WAIT;
			}
			break;
		case MSG1:
			if (x < 22)
			{
			state = MSG1;
			}
			else if (x == 22)
			{
			x = 0;
			state = MSG2;
			}
			break;
		case MSG2:
			if (x < 22)
			{
			state = MSG2;
			}
			else if (x == 22)
			{
			x = 0;
			state = MSG3;
			}
			break;
		case MSG3:
			if (x < 9)
			{
			state = MSG3;
			}
			else if (x == 9)
			{
			x = 0;
			state = MSG1;
			}
			break;
		default:
			break;
	}

	switch(state) 
	{
		case START:
			break;
		case WAIT:
			break;
		case MSG1:
			x++;
			if (x == 1) 
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "CS120B is Legend");
			}
			else if (x == 2)
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "S120B is Legend.");
			}
			else if (x == 3) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "120B is Legend..");
                        }
			else if (x == 4) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "20B is Legend...");
                        }
			else if (x == 5) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "0B is Legend... ");
                        }
			else if (x == 6) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "B is Legend... w");
                        }
			else if (x == 7) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " is Legend... wa");
                        }
			else if (x == 8) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "is Legend... wai");
                        }
			else if (x == 9) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "s Legend... wait");
                        }
			else if (x == 10) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " Legend... wait ");
                        }
			else if (x == 11) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "Legend... wait f");
                        }
			else if (x == 12) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "egend... wait fo");
                        }
			else if (x == 13) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "gend... wait for");
                        }
			else if (x == 14) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "end... wait for ");
                        }
			else if (x == 15) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "nd... wait for i");
                        }
			else if (x == 16) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "d... wait for it");
                        }
			else if (x == 17) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "... wait for it ");
                        }
			else if (x == 18) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, ".. wait for it D");
                        }
			else if (x == 19) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, ". wait for it DA");
                        }
			else if (x == 20) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " wait for it DAR");
                        }
			else if (x == 21) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "wait for it DARY");
                        }
			else if (x == 22) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "ait for it DARY!");
                        }
			break;
		case MSG2:
			x++;
			if (x == 1) 
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "it for it DARY! ");
			}
			else if (x == 2)
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "t for it DARY!  ");
			}
			else if (x == 3) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " for it DARY!   ");
                        }
			else if (x == 4) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "for it DARY!    ");
                        }
			else if (x == 5) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "or it DARY!     ");
                        }
			else if (x == 6) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "r it DARY!      ");
			state = MSG2;
                        }
			else if (x == 7) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " it DARY!       ");
                        }
			else if (x == 8) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "it DARY!        ");
                        }
			else if (x == 9) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "t DARY!         ");
                        }
			else if (x == 10) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " DARY!          ");
                        }
			else if (x == 11) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "DARY!           ");
                        }
			else if (x == 12) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "ARY!            ");
                        }
			else if (x == 13) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "RY!             ");
                        }
			else if (x == 14) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "Y!              ");
                        }
			else if (x == 15) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "!               ");
                        }
			else if (x == 16) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "                ");
                        }
			else if (x == 17) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "               C");
                        }
			else if (x == 18) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "              CS");
                        }
			else if (x == 19) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "             CS1");
			state = MSG2;
                        }
			else if (x == 20) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "            CS12");
                        }
			else if (x == 21) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "           CS120");
                        }
			else if (x == 22) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "          CS120B");
                        }
			break;
		case MSG3:
			x++;
			if (x == 1) 
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "         CS120B ");
			}
			else if (x == 2)
			{
			LCD_ClearScreen();
			LCD_DisplayString(1, "        CS120B i");
			}
			else if (x == 3) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "       CS120B is");
                        }
			else if (x == 4) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "      CS120B is ");
                        }
			else if (x == 5) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "     CS120B is L");
                        }
			else if (x == 6) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "    CS120B is Le");
                        }
			else if (x == 7) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "   CS120B is Leg");
                        }
			else if (x == 8) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, "  CS120B is Lege");
                        }
			else if (x == 9) 
			{
                        LCD_ClearScreen();
                        LCD_DisplayString(1, " CS120B is Legen");
                        }
			break;
		default:
			break;
	}
return state;
}

int main(void)
{
DDRC = 0xFF;	PORTC = 0x00;
DDRD = 0xFE;	PORTD = 0x01;

LCD_init();

static task task1;
task *tasks[] = { &task1 };
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

task1.state = START;
task1.period = 500;
task1.elapsedTime = task1.period;
task1.TickFct = &Message;

TimerSet(10);
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
		tasks[i]->elapsedTime += 10;
		}
	while(!TimerFlag);
	TimerFlag = 0;
	}
return 0;
}
