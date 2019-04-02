/*
 * File:   main.c
 * Author: austinschlegel
 *
 * Created on April 1, 2019, 8:07 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18f4331.h>
#include "config.h"
#include "lcd.h"

/*
 * File:   led_message.c
 * Author: Flynn
 *
 * Created on March 9, 2019, 9:10 PM
 */


void main(void) 
{  
    TRISB = 0x00; //set port B as output
    OSCCON = 0x76;

    LCD_Init();
    
    while(1)
    {
        
        LATBbits.LATB0 =~LATBbits.LATB0; //inverse port RB0 LED
        LCD_String_xy(1,5,"ASS");
        __delay_ms(1000);
        LCD_Clear();
 

        LATBbits.LATB0 =~LATBbits.LATB0; //inverse port RB0 LED
        LCD_String_xy(1,5,"ALERT");
        __delay_ms(1000);
        LCD_Clear();

    }
}
