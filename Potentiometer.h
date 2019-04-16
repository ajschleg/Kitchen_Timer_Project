/* 
 * File:   Potentiometer.h
 * Author: austinschlegel
 *
 * Created on April 8, 2019, 4:10 PM
 */

#ifndef POTENTIOMETER_H
#define	POTENTIOMETER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic18f4331.h>
#include "config.h"

    void InitADC(void);
    U16 ReadPot(void);
    U8 getPotDivider(U8 maxPotValue, U8 numMenuOptions);



#ifdef	__cplusplus
}
#endif

#endif	/* POTENTIOMETER_H */

