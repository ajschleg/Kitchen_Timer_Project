/* 
 * File:   menu.h
 * Author: Poglodyte
 *
 * Created on April 14, 2019, 4:35 PM
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <string.h>
    
void setTimer(void);
U8 PB(void);
void toggleTimer(U8);

    char menuOptionStrings[5][10];



#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

