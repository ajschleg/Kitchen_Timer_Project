/* 
 * File:   lcd.h
 * Author: austinschlegel
 *
 * Created on April 1, 2019, 8:23 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pic18f4331.h>
#include <xc.h>
#include "config.h"

#define RS LATB1                   /* PORTB 1 pin is used for Register Select */
#define EN LATB2                   /* PORTB 2 pin is used for Enable */
#define ldata LATD                 /* PORTD is used for transmitting data to LCD 8 bit mode*/

    
void LCD_Init(void);
    
void LCD_Command(char);

void LCD_Char(char data);

void LCD_Clear(void);

void LCD_Char_xy(char ,char ,const char );
void LCD_String_xy(char, char, const char*);


void LCD_String(const char *);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

