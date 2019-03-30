
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "led_message.h"

/*
 * File:   led_message.c
 * Author: Flynn
 *
 * Created on March 9, 2019, 9:10 PM
 */


void main(void) 
{  
    TRISBbits.RB0 = 0;
    OSCCON = 0x76;
    //LATB = 0xFF;
    //LATBbits.LATB0 = 1;
    //PORTB= 0x01;
    while(1)
    {
        LATBbits.LATB0 =~LATBbits.LATB0;
        for(int i = 0; i < 20; i++)
        {
            __delay_ms(50);
        }
    }
}
