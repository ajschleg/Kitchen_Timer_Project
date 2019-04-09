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

    count = 0;
    
    
    //Init_timer0();
    LCD_Init();
    InitPot();
   

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
    
    //LCD_String_xy(2,0,"HELLO");
    
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
        
        result = ReadPot();
        StartDHT11();
        
        if(CheckResponseDHT11())
        {
            // Read the 40 bit received message
            RH_byte1 = ReadDHT11();
            RH_byte2 = ReadDHT11();
            T_byte1 = ReadDHT11();
            T_byte2 = ReadDHT11();
            CheckSum = ReadDHT11();
            
            u8_to_BCD(1,0,RH_byte1);
            u8_to_BCD(1,4,RH_byte2);
            u8_to_BCD(2,0,T_byte1);
            u8_to_BCD(2,4,T_byte1);
            u8_to_BCD(2,8,CheckSum);
            
            if(CheckSum == ((RH_byte1+RH_byte2+T_byte1+T_byte2) & 0xFF) || temp_override)
            {
                Toggle_Blue();
                //LCD_String_xy(1, 8, "T:  C");
                //LCD_String_xy(2, 8, "RH: %");
                u8_to_BCD(1,13, T_byte1);
                u8_to_BCD(2,13, RH_byte1);
            }
            else
            {
                Toggle_Red();
            }
        }
    }
}

__interrupt() void ISR(void)
{
    if(INTCONbits.T0IF)
    {
        Toggle_Green();

        u8_to_BCD(count,1,0);

        TMR0 = 0xE17A;
        INTCONbits.T0IF = 0;
    }
    count++;
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
