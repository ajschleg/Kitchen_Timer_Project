#include <stdio.h>
#include <pic18f4331.h>
#include <xc.h>

#include "TempSensor.h"
#include "led.h"
#include "lcd.h"

void StartDHT11()
{
    //I think Im going to have to replace delays with timers
    DHT11_ddr = 0; //configure as output
    DHT11 = 0; //send 0
    
    __delay_ms(18); //low retention time
    
    DHT11 = 1; //send 1
    
    __delay_ms(30); //pulled wait
    DHT11_ddr = 1; //make input
    
}

void CheckResponseDHT11()
{
    //maybe use timer here
    check = 0;
    __delay_us(40);
    if (DHT11 == 0)
    {
        __delay_us(80); //response signal
    }
    if (DHT11 == 1) 
    {
        check = 1; 
        __delay_us(40); //ready to receive data
    }
}
    
U8 ReadDHT11()
{
    U8 i, j;
    U8 tiout_count;
    U8 tiout;
    
    //check if tiout occurred
    Toggle_Blue();
    if(tiout)
    {
        Toggle_Red();
        return 0;
    }
    
    for(j = 0; j < 8; j++)
    {
        while(!DHT11)
        {//Wait until LA0 goes HIGH
            tiout_count++;
            if(tiout_count>100)
            {
                tiout = 1;
                break;
            }
        }
            

        __delay_us(28); // If we wait 30 us and the signal is still high we know it is "1"
        
        if(DHT11 == 0)
        {
            i &= ~(1<<(7 - j)); //Clear bit (7-b)
        }
        else //we know it is "1"
        {
            i |= (1 << (7 - j)); //Set bit (7-b)
        }

        while(DHT11)
        {
            //Wait until LA0 goes LOW
            tiout_count++;
            if(tiout_count > 100)
            {
                tiout = 1;
                break;
            }
        }
    }
    Toggle_Blue();
    return i;
}


