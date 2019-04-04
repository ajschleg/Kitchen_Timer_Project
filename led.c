#include <stdio.h>
#include <xc.h>
#include <pic18f4331.h>
#include "led.h"

void Toggle_Red()
{
    LATBbits.LATB0 =~LATBbits.LATB0; //inverse port RB0 LED
}
void Toggle_Blue()
{
    LATBbits.LATB3 =~LATBbits.LATB3; //inverse port RB3 LED
}