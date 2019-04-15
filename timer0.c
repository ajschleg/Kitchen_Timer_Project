#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "config.h"
#include "timer0.h"
#include "led.h"
#include "lcd.h"


void Init_timer0(void)
{
    TMR0IE = 0;
    delay_amt = 10000;

    TMR0 = 0x00; //Clear the timer0 register
    /*TMR0 = 
     40MHz/4 = 10MHz
     10MHz = 0.1us
     T overflow = 25.5us
     so, to get 10us set TMR0 = 15.5 (25.5 - 15.5)*/
    TMR0 = 0xE6; // 10uS
    T0CON = 0xC8; //8bit no prescalar
    INTCONbits.GIE = 1; // Global interrupt enable 
    INTCONbits.TMR0IE = 1; // Enable interrpt for when timer 0 overflows 
}

void _ms_delay(U16 delay)
{
    //stop timer interrupt for short time
    TMR0IE = 0;
   
    delay_amt = delay;
    
    TMR0 = 0x00;
    //set the timer so that it will overflow and interrupt every 1ms
    TMR0 = 0xD7; //set to start at 25/255
    T0CON = 0xC5; //set timer to 8 bit and prescalar of 64
    TMR0IE = 1;     // enable timer interrupt
    
    ms_delay_flg = 1;
    while(ms_delay_flg)
    { 
        //get interrupted
    }   
    
}

