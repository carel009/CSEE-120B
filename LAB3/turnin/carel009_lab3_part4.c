/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #3  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void)
{
    DDRA = 0x00;	PORTA = 0xFF;
    DDRB = 0xFF;	PORTA = 0x00;
    DDRC = 0xFF;	PORTA = 0x00;
    while (1)
    {
    PORTB = (PINA & 0xF0) >> 4;
    PORTC = (PINA & 0x0F) << 4;
    }
    return 0;
}
