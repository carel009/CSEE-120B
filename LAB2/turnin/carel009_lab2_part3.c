/*	Author: Christopher Arellano
 *  Partner(s) Name: 
 *	Lab Section: 026
 *	Assignment: Lab #2  Exercise #3
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
    unsigned char tmpc = 0x00;
    while (1) 
    {
    unsigned char cntavail = ((PINA & 0x08)>>3) + ((PINA & 0x04)>>2) + ((PINA & 0x02)>>1) + (PINA & 0x01);
    cntavail = 0x04 - cntavail;
    if (cntavail == 0x00)
    {
    tmpc = (tmpc & 0x70) | 0x80;
    }
    else
    {
    tmpc = (tmpc & 0xF0) | cntavail;
    }
    PORTC = tmpc;
    }
    return 0;
}
