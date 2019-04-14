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
#include "TempSensor.h"
#include "Potentiometer.h"

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
    //TRISCbits.RC0 = 1; // Assign RE0 as input from PB
    OSCCON = 0x76;

    ms_delay_flg = 0;
    us_delay_flg = 0;
    
    s_count = 0;
    us_count = 0;
    

    //Init_timer0();
    ei();
    InitPot();
    LCD_Init();


    U8 status = 0;
    U16 result = 0;
    U8 CheckSum;
    U8 RH_byte1;
    U8 RH_byte2;
    U8 T_byte1;
    U8 T_byte2;
    U8 temp_override = 0;
    
    Toggle_Red();
    Toggle_Blue();
    
    LCD_String_xy(2,0,"HELLO");
    
    
    while(1)
    {
        //Toggle_Red();
        //__delay_ms(50);
        /*do{
            status = PORTCbits.RC0;         // Read the pin
            __delay_ms(10);                   // Introduce a delay between each read
        }while(!status);                    // keep reading till a LOW
        __delay_ms(100);                      // Switch press detected  - de-bouncing delay
        status = PORTCbits.RC0;             // read again
        if (!status)                        // check the pin status
        {
            // Switch Pressed, Do something for showing off
        }*/
        _us_delay(60000);
        Toggle_Blue();
        result = ReadPot();
        u8_to_BCD(1,0,result);

    }
}

// <editor-fold defaultstate="collapsed" desc="comment">
void __interrupt () ISR(void)
{
    //Maybe need to check for overflow and int enable bits for timer 0, but timer should be only thing causing interrupt so 
    //probably dont need to worry about it
    
    //check if millisecond
    if(TMR0IF)
    {

        ms_count++;
        
        if(ms_count == delay_amt)
        {
            //reset
            ms_delay_flg = 0;
            ms_count = 0;
            TMR0IE = 0;
        }
        
        TMR0 = 0xD7;
        TMR0IF = 0;
    }
}




void u8_to_BCD(U8 row, U8 column, U16 num)
{
    U8 hundreds;
    U8 tens;
    U8 ones;
    
    hundreds = num/100 + 48;
    tens = (num%100)/10 + 48;
    ones = (num%10) + 48;
    LCD_Char_xy(row,column,hundreds);
    LCD_Char_xy(row,column+1,tens);
    LCD_Char_xy(row,column+2,ones);
    LCD_Char_xy(row,column+3, ' ');
    LCD_Char_xy(row,column+4, ' '); //clear the space after the count. for some reason there are random numbers here.
}
