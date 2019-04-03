/*
 * File:   main.c
 * Author: austinschlegel
 *
 * Created on April 1, 2019, 8:07 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic18f4331.h>

#include "config.h"
#include "lcd.h"
#include "led.h"
#include "timer0.h"

/*
 * File:   led_message.c
 * Author: Flynn
 *
 * Created on March 9, 2019, 9:10 PM
 */


void main(void) 
{  
    TRISB = 0x00; //set port B as output
    TRISD = 0x00;       /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    OSCCON = 0x76;

    
    LCD_Init();
    Init_timer0();
    
    while(1)
    {
        LCD_String_xy(1,5,"ASS");
        __delay_ms(50);
        LCD_Clear();
 
        Blink_Blue();
        LCD_String_xy(1,5,"ALERT");
        __delay_ms(50);
        LCD_Clear();

    }
}

__interrupt() void ISR(void)
{

    if(INTCONbits.T0IF)
    {
        //sprintf(buffer, "%d", counter);
        Blink_Red();


        TMR0 = 0xB3B4;
        INTCONbits.T0IF = 0;
    }
}
