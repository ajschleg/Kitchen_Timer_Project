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

void u8_to_BCD(U16 num);

U16 count;

void main(void) 
{  
    TRISB = 0x00; //set port B as output
    TRISD = 0x00;       /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    //TRISCbits.RC0 = 1; // Assign RE0 as input from PB
    OSCCON = 0x76;

    count = 0;
    
    LCD_Init();

    Init_timer0();

    U8 status = 0;
    Toggle_Red();
    Toggle_Blue();
    while(1)
    {
        __delay_ms(50);
        /*do{
            status = PORTCbits.RC0;         // Read the pin
            __delay_ms(10);                   // Introduce a delay between each read
        }while(!status);                    // keep reading till a LOW
        __delay_ms(100);                      // Switchpress detected  - debouncing delay
        status = PORTCbits.RC0;             // read again
        if (!status)                        // check the pin status
        {
            // Switch Pressed, Do something for showing off
        }*/
        LCD_String_xy(2,0,"HELLO");
        while(1)
        {
            
        }
    }
}

__interrupt() void ISR(void)
{
    if(INTCONbits.T0IF)
    {
        Toggle_Green();

        u8_to_BCD(count);

        TMR0 = 0xE17A;
        INTCONbits.T0IF = 0;
    }
    count++;
}

void u8_to_BCD(U16 num)
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
}
