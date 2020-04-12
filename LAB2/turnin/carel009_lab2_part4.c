/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #2  Exercise #4
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
    DDRB = 0x00;	PORTB = 0xFF;
    DDRC = 0x00;	PORTC = 0xFF;
    DDRD = 0xFF;	PORTD = 0x00;
    unsigned char weightsum = 0x00;
    unsigned char weighttot = 0x00;
    unsigned char weightdif = 0x00;
    while (1)
    {
    weightsum = PINA + PINB + PINC;
    if(weightsum > 0x8C)
    {
    weighttot = 0x01;
    }
    if(weightsum <= 0x8C)
    {
    weighttot = 0x00;
    }
    if(abs(PINA - PINC) > 0x50)
    {
    weightdif = 0x02;
    }
    if(abs(PINA - PINC) <= 0x50)
    {
    weightdif = 0x00;
    }
    PORTD = (weightsum & 0xFC) | weightdif | weighttot;
    }
    return 0;
}
