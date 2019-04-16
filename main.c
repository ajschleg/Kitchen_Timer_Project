/*
 * File:   main.c
 * Author: austinschlegel
 *
 * Created on April 1, 2019, 8:07 PM
 */
void turnSpeakerOn(void);
void turnSpeakerOff(void);

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

/*
 * File:   led_message.c
 * Author: austinschlegel
 *
 * Created on March 9, 2019, 9:10 PM
 */



void main(void) 
{  
    int potDivider;
    char menuOptionStrings[5][10];
    
//    menuOptionStrings[0] = (char*)malloc(10);
    strcpy(menuOptionStrings[0], "Set Timer");
    strcpy(menuOptionStrings[1], "Option 2");
    strcpy(menuOptionStrings[2], "Option 3");
    strcpy(menuOptionStrings[3], "Option 4");
    strcpy(menuOptionStrings[4], "Option 5");
    
    
    TRISB = 0x00; //set port B as output
    TRISD = 0x00;       /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    TRISCbits.RC0 = 1; // Assign RE0 as input from PB
    OSCCON = 0x76;
    
    //stop song notes and delay period
    unsigned int stopsong[] = {1,0};
    unsigned int delay_period0[] = {1,0};

    //birthday song notes and delay period
	U8 birthday[] = {C4,C4,D4,C4,F4,E4,C4_1,C4,D4,C4,G4,F4,C4_1,C4,C5,A4,F4,E4,D4,B4b,B4b,A4,F4,G4,F4,0};
	U8 delay_period[] = {1,1,2,2,2,3,1,1,2,2,2,3,1,1,2,2,2,2,3,1,1,2,2,2,3,0};

    U8 curr_duty_cycle = 0;
 
    //Init_timer0();
    ei();
    InitADC();
    //LCD_Init();
    InitPWM();
    setDutyCycle(curr_duty_cycle);

    U8 status = 0;
    U16 result = 0;
    U16 temperature = 0;
    U8 wait = 0;
    
    potDivider = getPotDivider(255, 5);

    
    
    ms_delay_flg = 0;
    
    s_count = 0;
    
    counter = 0;
    
//    Toggle_Red();
//    Toggle_Blue();
    U8 selection;
    
    while(1)
    {
        
        // POTENTIOMETER
        result = ReadPot();
        selection = result / potDivider;
        LCD_String_xy(1,8,menuOptionStrings[selection]);
        
        
        // PUSH BUTTON
        do{
            status = PORTCbits.RC0;         // Read the pin
            _ms_delay(10);                   // Introduce a delay between each read
        }while(!status);                    // keep reading till a LOW
        _ms_delay(100);                      // Switch press detected  - de-bouncing delay
        status = PORTCbits.RC0;             // read again
        if (!status)                        // check the pin status
        {
            // Button Pressed
            Toggle_Red();
            
            // Do something based on menu selection
            switch(selection) {
                case 0 : {
//                    setTimer();
                    turnSpeakerOn();
                    break;
                }
                case 1 : {  
//                    pauseTimer();
                    turnSpeakerOff();
                    break;
                }
            }
                    
        }
        
//        for (wait=0 ; wait<26 ; wait++)                     // loop 26 times 
//        {
//                PR2 = (birthday[wait]/2);                       // generate PWM period
//                tone_out(birthday[wait],delay_period[wait]*6000);
//        }
        temperature = ReadTemp();
        //u8_to_BCD(2,0,temperature);

//        _ms_delay(100);
        
//        Toggle_Blue();
       
        //u8_to_BCD(1,0,result);    
        
    }
}

// <editor-fold defaultstate="collapsed" desc="comment">
void __interrupt () ISR(void)
{
    //Maybe need to check for overflow and int enable bits for timer 0, but timer should be only thing causing interrupt so 
    //probably dont need to worry about it
    //check if timer 0 interrupt flag
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

void setTimer() {
    // set seconds
    
        // push button to go to mins
    
    // set mins
    
        // push button to go to hrs
    
    // set hrs
    
        // push button to finish
    
    
    // maybe display a start/cancel at this point(shift between with pot)
    
    
}

void turnSpeakerOn(void) {
//    curr_duty_cycle += 10;
//    curr_duty_cycle = curr_duty_cycle % 110;
//    setDutyCycle(curr_duty_cycle);
    setDutyCycle(50);
}

void turnSpeakerOff(void) {
    setDutyCycle(0);
}
