
#include "Potentiometer.h"

void InitADC(void)
{
    PORTAbits.AN0 = 1;
    PORTAbits.AN1 = 1;
    
    //Potentiometer is measured through ADC. So set up ADC register to read from AN0
    ADCON0 = 0x01; //single channel,single shot,and AD on
    ADCON1 = 0x10; //FIFO enabled
    ADCON2 = 0x00; //left justified and Fosc/2
    ADCON3 = 0xA0; //unimplemented
    ADCHS = 0x00; //AN0 and AN1 as input, Group A and group b
    ANSEL0 = 0x03; //AN0 as analog, AN1 as analog
    
    ADRESH=0;           /*Flush ADC output Register*/
    ADRESL=0; 
}

U16 ReadPot(void)
{
    //Read pot will return pot value
    ADCON0bits.ACMOD0 = 0;
    ADCON0bits.ACMOD1 = 0; //make group a taken and converted
    
    U16 result;
    
    ADCON0bits.GO = 1; //GO!
    while(ADCON0bits.GO == 1)
        ; //wait until conversion is done
    result = 0x00; //reset
    result = ADRESH;              

    return result;
}



