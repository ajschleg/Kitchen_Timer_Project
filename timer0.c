#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "config.h"
#include "timer0.h"
#include "led.h"
#include "lcd.h"


void Init_timer0(void)
{

    TMR0 = 0x0BFA; //Clear the timer0 register 
    T0CON = 0x84; //16bit and 32 prescalar
    INTCONbits.GIE = 1; // Global interrupt enable 
    INTCONbits.TMR0IE = 1; // Enable interrpt for when timer 0 overflows 
}


