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
    
//    menuOptionStrings[0] = (char*)malloc(10);
    strcpy(menuOptionStrings[0], "Set Timer ");
    strcpy(menuOptionStrings[1], "Pause Time");
    strcpy(menuOptionStrings[2], "Res. Timer");
    strcpy(menuOptionStrings[3], "Option 4  ");
    strcpy(menuOptionStrings[4], "Bonus     ");


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
    tmr_expire = 0;
    
    Toggle_Red();
    Toggle_Blue();
    potDivider = getPotDivider(255, 5);

    LCD_String_xy(2,3," F");
    turnSpeakerOff();

    while(1)
    {
        
//        for (wait=0 ; wait<26 ; wait++)                     // loop 26 times 
//        {
//                PR2 = (birthday[wait]/2);                       // generate PWM period
//                tone_out(birthday[wait],delay_period[wait]*6000);
//        }        
        
        //poll till button is pressed
        while(PORTCbits.RC0)
        {
            result = ReadPot();
            selection = result / potDivider;
            //LCD_String_xy(1,6,menuOptionStrings[selection]);
            LCD_Char_xy(1,6,selection+48);
            u8_to_BCD(1,0,s_count);
            temperature = ReadTemp();
            u8_to_BCD(2,0,temperature);
        }
        // Button Pressed
        Toggle_Red();

        // Do something based on menu selection
        switch(selection) {
            case 0 : { //set timer
                setTimer();
                break;
            }
            case 1 : {  //pause
                toggleTimer(0);
                break;
            }
            case 2 : { //resume
                toggleTimer(1);
                break;
            }
            case 3 : { //bonus

            }
        }
                
    }
}

void __interrupt () ISR(void)
{
    // Check if timer 0 interrupt flag want to interrupt as little as possible
    // Also want timer ISR as small as possible to keep good time
    if(TMR0IF)
    {
        s_count--;
        if(s_count <= 0)
        {
            //turn off the timer and play the tune
            TMR0ON = 0;
            turnSpeakerOn();
            __delay_ms(1000);
            turnSpeakerOff();
            Toggle_Red();
        }
        TMR0 = 0x0BFA; 
        TMR0IF = 0;
    }
}




void u8_to_BCD(U8 row, U8 column, U16 num)
{
    //this function takes 5*30ms to finish
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
