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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum states{start,left,middle,right,idle}state;

volatile unsigned char TimerFlag =0; //this is for TimerISR

unsigned long _avr_timer_M =1;
unsigned long _avr_timer_cntcurr =0;
char holder;


char getL()
{
return PINA&0x01;
}
char getM()
{
return (PINA>>1)&0x01;
}
char getR()
{
return (PINA>>2)&0x01;
}
void TimerOn() {

TCCR1B= 0x0B;

OCR1A = 125;

TIMSK1 = 0x02;

TCNT1 = 0;
_avr_timer_cntcurr = _avr_timer_M;
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
         _avr_timer_cntcurr = _avr_timer_M;
        }


}


void TimerSet(unsigned long M)
{
_avr_timer_M = M;
_avr_timer_cntcurr = _avr_timer_M;
}
void Tick()
{
 switch(state) // transition actions
	{
	case start: state =left; break;
	case left: if(getL() ==1){state =idle;holder=0x01;}else{state = middle;}  break;
	case middle: if(getM() ==1){state = idle;holder=0x02;}else{state = right;} break;
	case right: if(getR()==1){state = idle;holder=0x04;} else{state=left;}break;
	case idle: if(getL()==1||getR()==1||getM()==1){state = left;}break;
	default: state =start; break;
	}
// state actions
switch(state)
	{
	case start: break;
	case left:  PORTB = 0x01; break;
	case middle: PORTB = 0x02; break;
	case right: PORTB = 0x04; break;
	case idle:  PORTB = holder; break;
	default: break;
	}	

}




int main(void) {
    
	DDRB = 0xFF;
	PORTB = 0x00;

	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;


    while (1) 
    {
	tmpB = ~tmpB;
	PORTB = tmpB;
	while (!TimerFlag);
	TimerFlag =0;
	Tick();
    }
    return 0;
}
