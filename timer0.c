#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "timer0.h"
#include "led.h"
#include "lcd.h"


void Init_timer0(void)
{
    TMR0 = 0; //Clear the timer0 register
    INTCONbits.GIE = 1; // Global interrupt enable 
    INTCONbits.TMR0IE = 1; //enable interrpt for when timer overflows
    /* TMR0 = Max value of timer - ((delay in seconds * osc freq) / (4 * prescalar)
     TMR0 = 65535 - (1 * 8000000) / ( 4* 256)*/
    TMR0 = 0xE17B; //1ms
    T0CON = 0x87;
}

