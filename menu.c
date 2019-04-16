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
    // set seconds
    
        // push button to go to mins
    
    // set mins
    
        // push button to go to hrs
    
    // set hrs
    
        // push button to finish
    
    
    // maybe display a start/cancel at this point(shift between with pot)
    
    
}

void PB(U8 selection, U8 status)
{
    //status takes 110ms
    do{
        status = PORTCbits.RC0;         // Read the pin
        __delay_ms(10);                   // Introduce a delay between each read
    }while(!status);                    // keep reading till a LOW
    __delay_ms(100);                      // Switch press detected  - de-bouncing delay
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
}
