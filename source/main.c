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

ISR(TIMER1_COMPA_vect)
{
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr ==0)
        {

         TimerISR();
         _avr_timer_cntcurr = _avr_tiemr_M;
        }


}


void TimerSet(unsigned long M)
{
_avr_timer_M = M;
_avr_timer_cntcurr = _avr_timer_M;
}




int main(void) {
    
	DDRB = 0xFF;
	PORTB = 0x00;

	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;


    while (1) 
    {

    }
    return 1;
}
