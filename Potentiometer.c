
#include "Potentiometer.h"

void InitPot(void)
{
    //Potentiometer is measured through ADC. So set up ADC register to read from AN0
    ADCON0 = 0x03;
    ADCON1 = 0x10;
    ADCON2 = 0x00;
    ADCON3 = 0x00;
    ADCHS = 0x00;
    ANSEL0 = 0x01;
}

U8 ReadPot(void)
{
    //Read pot will return pot value
    
    U8 result;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1)
        ;
    result = 0x00; //reset
    result = ADRESH; //set result equal to the value read


    u8_to_BCD(result, 2, 8);
    return result;
}



