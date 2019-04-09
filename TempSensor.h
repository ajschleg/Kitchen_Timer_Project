/* 
 * File:   TempSensor.h
 * Author: austinschlegel
 *
 * Created on April 7, 2019, 4:59 PM
 */

#ifndef TEMPSENSOR_H
#define	TEMPSENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <xc.h>
#include <pic18f4331.h>
#include "config.h"

#define DHT11_ddr TRISCbits.RC4
#define DHT11 LATCbits.LATC4
    

   void StartDHT11(void);
   void CheckResponseDHT11(void);
   U8 ReadDHT11(void);
   


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPSENSOR_H */

