/*	Author: jmach017
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


volatile unsigned char TimerFlag =0; //this is for TimerISR

unsigned long _avr_timer_M =1;
unsigned long _avr_timer_cntcurr =0;



void TimerOn() {

TCCR1B= 0x0B;

OCR1A = 125;

TIMSK1 = 0x02;

SREG |= 0x80;


}
void TimerOff()
{

TCCR1B = 0x00;

}
void TimerISR(){
TimerFlag=1;

}

ISR


int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {

    }
    return 1;
}
