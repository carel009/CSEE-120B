/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #2
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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) 
    {
    unsigned char cntavail = ((PINA & 0x08)>>3) + ((PINA & 0x04)>>2) + ((PINA & 0x02)>>1) + (PINA & 0x01);
    cntavail = 0x04 - cntavail;
    PORTC = cntavail;
    }
    return 0;
}
