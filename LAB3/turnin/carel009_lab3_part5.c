/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #3  Exercise #5
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
    DDRD = 0x00;	PORTD = 0xFF;
    DDRB = 0xFE;	PORTB = 0x01;
    unsigned char tmpB = 0x00;
    unsigned short sense = 0x0000;
    unsigned char disp = 0x00;
    while (1)
    {
    tmpB = PINB & 0x01;
    sense = (PIND << 1) | tmpB;
    if (sense >= 0x0046)
    {
    disp = 0x02;
    }
    if ((sense > 0x0005) && (sense < 0x0046))
    {
    disp = 0x04;
    }
    if (sense <= 0x0005)
    {
    disp = 0x00;
    }
    PORTB = disp;
    }
    return 0;
}
