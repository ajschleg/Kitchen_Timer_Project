#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "config.h"
#include "timer0.h"
#include "led.h"
#include "lcd.h"
#include "menu.h"
#include "Speaker.h"
#include "Potentiometer.h"

U8 PB_Pressed(void);

void setTimer() 
{
    // should clear or cancel current timer?
    toggleTimer(0);
    timer_hrs = 0;
    timer_mins = 0;
    timer_secs = 0;
    
    U8 potValue;

    // set divider for 60 values(seconds =  0:59)
    U8 potDivider = 255 / 60;
    
    // Display Timer
    two_digit_to_lcd(1, 0, timer_hrs);
    LCD_Char_xy(1, 2, ':');
    two_digit_to_lcd(1, 3, timer_mins);
    LCD_Char_xy(1, 5, ':');
    two_digit_to_lcd(1, 6, timer_secs);

    // set seconds
    while(!PB_Pressed()) {
        // blink seconds display


        // set seconds with potentiometer
        potValue = ReadPot() / potDivider;
        timer_secs = potValue < 60 ? potValue : 59;

        // update to lcd
        two_digit_to_lcd(1, 6, timer_secs);
    }    
    
    // delay (debounce)
    // extra wait to catch continued button press?
    while (PB_Pressed()) ;

    // pot divider still set for 60 values(minutes =  0:59)
    // set minutess
    while(!PB_Pressed()) {
        // blink minutes display

        // set minutes with potentiometer
        potValue = ReadPot() / potDivider;
        timer_mins = potValue < 60 ? potValue : 59;

        // display to lcd
        two_digit_to_lcd(1, 3, timer_mins);
    }

    // delay (debounce)
    // extra wait to catch continued button press?
    while (PB_Pressed()) ;    
    
    
    // set divider for 100 values(hrs = 0:99)
    potDivider = 255 / 100;
    // set hours
    while(!PB_Pressed()) {
        // blink hours display

        // set hours with potentiometer
        potValue = ReadPot() / potDivider;
        timer_hrs = potValue < 100 ? potValue : 99;

        // display to lcd
        two_digit_to_lcd(1, 0, timer_hrs);
    }

    // delay (debounce)
    // extra wait to catch continued button press?
    while (PB_Pressed()) ;   
    
    // finished setting timer
    // maybe display a start/cancel at this point(shift between with pot)
    
    // start/resume the timer
    toggleTimer(1);
}

void toggleTimer(U8 sel)
{
    TMR0ON = sel;
}

U8 PB_Pressed(void)
{
    return !PORTCbits.RC0;
}
