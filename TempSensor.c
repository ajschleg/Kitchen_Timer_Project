
#include "TempSensor.h"

void InitDHT11()
{

    TRISAbits.RA0 = 0; //configure as output
    LATAbits.LA0 = 0; //send 0
    __delay_ms(18);
    LATAbits.LA0 = 1; //send 1
    __delay_ms(30);
    TRISAbits.RA0 = 1;
        
}

void CheckDHT11()
{
    check = 0;
    __delay_us(40);
    if (LATAbits.LA0 == 0)
    {
        __delay_us(80);
    }
    if (LATAbits.LA0 == 1) 
    {
        check = 1; 
        __delay_us(40);
    }
}
    
U8 ReadDHT11(void)
{
    U8 i, j;
    for(j = 0; j < 8; j++)
    {
        while(!LATAbits.LA0); //Wait until PORTD.F0 goes HIGH
        
        __delay_us(30);
        
        if(LATAbits.LA0 == 0)
        {
            i &= ~(1<<(7 - j)); //Clear bit (7-b)
        }
        else 
        {
            i |= (1 << (7 - j)); //Set bit (7-b)
        }
        
        while(LATAbits.LA0); //Wait until PORTD.F0 goes LOW
        
        return i;

    }
}


