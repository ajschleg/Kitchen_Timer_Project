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

U8 u8_to_BCD(U8 num);

U8 count;

void main(void) 
{  
    TRISB = 0x00; //set port B as output
    TRISD = 0x00;       /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    OSCCON = 0x76;

    count = 0;
    
    Init_timer0();
    LCD_Init();

    
    while(1)
    {
        __delay_ms(50);
        //LCD_Clear();
 
        Blink_Blue();
        //LCD_String_xy(1,5,"ALERT");
        __delay_ms(50);
        //LCD_Clear();

    }
}

__interrupt() void ISR(void)
{

    if(INTCONbits.T0IF)
    {
        Blink_Red();

        u8_to_BCD(count);

        TMR0 = 0xE17A;
        INTCONbits.T0IF = 0;
    }
    count++;
}

U8 u8_to_BCD(U8 num)
{
    U8 hundreds;
    U8 tens;
    U8 ones;
    
    hundreds = num/100 + 48;
    tens = (num%100)/10 + 48;
    ones = (num%10) + 48;
    LCD_Char_xy(1,0,hundreds);
    LCD_Char_xy(1,1,tens);
    LCD_Char_xy(1,2,ones);

    
    return ones;
}
