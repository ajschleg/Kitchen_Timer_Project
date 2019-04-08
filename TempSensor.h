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

#define DHT11 LATAbits.LA1
#define DHT11_ddr TRISAbits.RA1;
    

   void InitDHT11(void);
   void CheckDHT11(void);
   U8 ReadDHT11(void);
   
   U8 check = 0;


#ifdef	__cplusplus
}
#endif

#endif	/* TEMPSENSOR_H */

