#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>
#include "TempSensor.h"
#include "config.h"

/*Using Lm35 analog temperature sensor*/
U16 ReadTemp(void)
{
    ADCON0bits.ACMOD0 = 1;
    ADCON0bits.ACMOD1 = 0; //make group b taken and converted

    U16 result;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1)
        ;
    result = 0x00; //reset
    result = (ADRESH+10)*9/5+32;              /*Combine 8-bit LSB and 2-bit MSB*/

    //turn off
    return result;
}
        
