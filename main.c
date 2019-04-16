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
#include "Speaker.h"
#include "menu.h"


void main(void) 
{  
    TRISB = 0x00; //set port B as output
    TRISD = 0x00;       /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    //TRISCbits.RC0 = 1; // Assign RE0 as input from PB
    OSCCON = 0x76;
    
    char menuOptionStrings[5][10];
    
//    menuOptionStrings[0] = (char*)malloc(10);
    strcpy(menuOptionStrings[0], "Set Timer");
    strcpy(menuOptionStrings[1], "Option 2");
    strcpy(menuOptionStrings[2], "Option 3");
    strcpy(menuOptionStrings[3], "Option 4");
    strcpy(menuOptionStrings[4], "Option 5");
    
    //stop song notes and delay period
    unsigned int stopsong[] = {1,0};
    unsigned int delay_period0[] = {1,0};

    //birthday song notes and delay period
	U8 birthday[] = {C4,C4,D4,C4,F4,E4,C4_1,C4,D4,C4,G4,F4,C4_1,C4,C5,A4,F4,E4,D4,B4b,B4b,A4,F4,G4,F4,0};
	U8 delay_period[] = {1,1,2,2,2,3,1,1,2,2,2,3,1,1,2,2,2,2,3,1,1,2,2,2,3,0};

 
    InitADC();
    LCD_Init();
    InitPWM();
    setDutyCycle(50);
    Init_timer0();

    
    U8 status = 0;
    U16 result = 0;
    U16 temperature = 0;
    U8 wait = 0;
    U8 potDivider = 0;
    U8 selection = 0;
    
    s_count = 0;
    
    Toggle_Red();
    Toggle_Blue();
    potDivider = getPotDivider(255, 5);

    LCD_String_xy(2,3," F");
    
    while(1)
    {
        
//        for (wait=0 ; wait<26 ; wait++)                     // loop 26 times 
//        {
//                PR2 = (birthday[wait]/2);                       // generate PWM period
//                tone_out(birthday[wait],delay_period[wait]*6000);
//        }
        u8_to_BCD(1,0,s_count);
        result = ReadPot();
        
        
        selection = result / potDivider;
        LCD_String_xy(1,8,menuOptionStrings[selection]);
        
        
        // PUSH BUTTON
        PB(selection, status);
        u8_to_BCD(1,0,s_count);

        
        temperature = ReadTemp();
        u8_to_BCD(2,0,temperature);
        
        
    }
}

void __interrupt () ISR(void)
{
    // Check if timer 0 interrupt flag want to interrupt as little as possible
    // Also want timer ISR as small as possible to keep good time
    if(TMR0IF)
    {
        s_count++;
        TMR0 = 0x0BFA; 
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
