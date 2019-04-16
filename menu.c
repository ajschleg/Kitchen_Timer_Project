#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "config.h"
#include "timer0.h"
#include "led.h"
#include "lcd.h"
#include "menu.h"
#include "Speaker.h"




void setTimer() 
{
    s_count = 100;
    // set seconds

    
        // push button to go to mins
    
    // set mins
    
        // push button to go to hrs
    
    // set hrs
    
        // push button to finish
    
    
    // maybe display a start/cancel at this point(shift between with pot)
    
    
}

void toggleTimer(U8 sel)
{
    
    TMR0ON = sel;
}

U8 PB(void)
{
    if (PORTCbits.RC0)
    {
        return 0;
    }
    
    else
    {
        return 1;
    }
}
