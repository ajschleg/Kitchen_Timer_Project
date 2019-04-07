#include <stdio.h>
#include <xc.h>
#include <pic18f4331.h>
#include "led.h"

void Toggle_Red()
{
    red_led =~red_led; //inverse port RB0 LED
}
void Toggle_Blue()
{
    blue_led =~blue_led; //inverse port RB3 LED
}
void Toggle_Green()
{
    green_led =~green_led;
}
void Toggle_4(void)
{
    LATBbits.LATB5 =~LATBbits.LATB5;
}

