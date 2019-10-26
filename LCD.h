/*
 * LCD.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef LCD_H_
#define LCD_H_

#include<string.h>
#include <avr/io.h>
//#include "OS.h"
#define BITS_MODES    4
//#define FIRST_PINS

/* control pins*/
#define  RS     PA1
#define  RW     PA2
#define  E      PA3
#define DIRECTION_CTRL_PINS     DDRA
#define CTRL_OUTPUT_PINS        PORTA

#define CURSOR_OFF            0x0c
#define CURSOR_MoveToFirstLoc 0x80

/* set functions*/
#define BITS_8_MODES               0x38
#define BITS_4_MODES               0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define CLEAR_LCD                  0x01


/*output pins */

#define DIRECTION_DATA_PINS     DDRA
#define DATA_OUTPUT_PINS        PORTA



#define TAKE_FTCOMMAND(PORT,COMMAND)    PORT=(PORT&0x0F)|(COMMAND&0xF0)
#define TAKE_SCCOMMAND(PORT,COMMAND)    PORT=(PORT&0x0F)|((COMMAND&0x0F)<<4)



#include"INTERFACE.h"
#include"UNIT_types.h"
#include"MICRO_setting.h"

typedef enum {PENDING=0, COMPLETED=1}enum_status_t;

enum_status_t LCD_sendCommand(unit8 command);
enum_status_t LCD_displayChar(uint8_t data);
enum_status_t LCD_displayStr(uint8_t* data);
void LCD_init(void);
enum_status_t LCD_displayString(const char *Str);
enum_status_t LCD_gotoRawCol(unit8 row, unit8 col);
void LCD_IntToStr(int data);
void LCD_displayStrRowCol(unit8 row,unit8 col, char *Str);
void LCD_clearScreen(void);
#endif /* LCD_H_ */
