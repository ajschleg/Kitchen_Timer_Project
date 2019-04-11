/* 
 * File:   timer0.h
 * Author: austinschlegel
 *
 * Created on April 2, 2019, 10:22 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "config.h"
    void Init_timer0(void);

    void _ms_delay(U16);
    void _us_delay(U16);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

