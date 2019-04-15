#include <stdio.h>
#include <xc.h>
#include <pic18f4331.h>
#include "config.h"
#include "Speaker.h"


void InitPWM(void)
{
    //use ccp2con and timer 2 
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;
    //CCP1CON = 0x0A; //PWM mode
    
    PR2 = 249;
    
    CCPR1L = 0x00;             // Initialize the PR2 registers
    
    // timer 2 setup 
    T2CONbits.T2CKPS1 = 1;            // Timer 2 prescaler 
	T2CONbits.T2CKPS0 = 1;            // Timer 2 prescaler = 16
	T2CONbits.TMR2ON = 1;             // Turn on Timer 2.
    
    
    TRISCbits.RC2 = 0x00; //clkear bit 2
    
//    CCP1CON = 0b00001100;
//    TRISC = 0b11111001;
//    T2CON = 0b00000100;
//    PR2 = 249;
//    CCPR1L = 25;
    
    
//    while(1) {
//        CCPR1L = 125;
//        _delay(125000);
//    }
}

void setDutyCycle(U8 duty_cycle)
{
    CCP1CON = (CCP1CON & 0b00001111) | (0b00110000 & ((unsigned int)(duty_cycle << 4)));
	CCPR1L = duty_cycle >> 2;
}

void tone_out(unsigned char tone , unsigned int delay) //produce duty cycle & keep tone playing for delay time
{
	while(delay-- > 0)
	{
		setDutyCycle(tone);		//generate PWM pulse width with delay period of note
	}							
}
