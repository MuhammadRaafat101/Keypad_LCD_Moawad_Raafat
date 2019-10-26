/*
 * Keypad.h Based on OS
 *
 * Created: 25/10/2019 3:02:56 PM
 *  Author: Mohamed Moawad
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"


#define N_col 3
#define N_row 3

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORT_C
#define KEYPAD_PORT_IN  PORT_C


/*
 * Function responsible for getting the pressed keypad key
 */
uint8_t KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
