/* 
 * File:   led.h
 * Author: austinschlegel
 *
 * Created on April 1, 2019, 10:08 PM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic18f4331.h>

    void Toggle_Red(void);
    void Toggle_Blue(void);
    void Toggle_Green(void);
    void Toggle_4(void);

#define blue_led LATBbits.LATB4
#define red_led LATBbits.LATB2
#define green_led LATBbits.LATB3


#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

