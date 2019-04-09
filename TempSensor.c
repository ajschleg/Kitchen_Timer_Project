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
    DHT11 = 0; //send 0 to to start
    
    __delay_ms(25); //let DHT11 detect signal
    
    DHT11 = 1; //send 1 to wait for response
    
    __delay_ms(30); //Pull up voltage to wait
    DHT11_ddr = 1; //set as input
    
}

U8 CheckResponseDHT11()
{
    //maybe use timer here
    __delay_us(40);
    if (DHT11 == 0)
    {
        __delay_us(80); //response signal
    }
    if (DHT11 == 1) 
    {
        __delay_us(50); //ready to receive data
        return 1; 
    }
}
    
U8 ReadDHT11()
{
    U8 i, j;
    U8 tiout_count;
    U8 tiout;
    
    //check if tiout occurred
    if(tiout)
    {
        Toggle_Red();
        LCD_String_xy(1,8,"TiOut");
        return 0;
    }
    else
    {
        LCD_String_xy(1,8,"     ");
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
            

        __delay_us(30); // If we wait 30 us and the signal is still high we know it is "1"
        
        if(DHT11 == 0) //it must be "0"
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
    return i;
}


