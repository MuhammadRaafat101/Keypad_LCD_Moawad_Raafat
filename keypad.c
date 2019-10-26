/*
 * Keypad.c Based on OS
 *
 * Created: 25/10/2019 3:02:56 PM
 *  Author: Mohamed Moawad
 */ 

#include "keypad.h"

uint8_t KeyPad_getPressedKey(void){
	uint8_t col,row,*data,retval = 0;

		for(col=0;col<N_col;col++)							/* loop for columns */
		{
			switch(col)
			{
				case 0:
					DIO_write(KEYPAD_PORT_OUT,PIN5,LOW);
					DIO_write(KEYPAD_PORT_OUT,PIN6,HIGH);
					DIO_write(KEYPAD_PORT_OUT,PIN7,HIGH);
				break;
				case 1:
					DIO_write(KEYPAD_PORT_OUT,PIN5,HIGH);
					DIO_write(KEYPAD_PORT_OUT,PIN6,LOW);
					DIO_write(KEYPAD_PORT_OUT,PIN7,HIGH);
				break;
				case 2:
					DIO_write(KEYPAD_PORT_OUT,PIN5,HIGH);
					DIO_write(KEYPAD_PORT_OUT,PIN6,HIGH);
					DIO_write(KEYPAD_PORT_OUT,PIN7,LOW);
				break;
				default:
				break;
			}
			for (row=0;row<N_row;row++)								/* loop for rows */
			{
				switch(row)
				{
					case 0:
						DIO_read(KEYPAD_PORT_IN,PIN2,data);
						if (LOW == *data)
						{
							retval = (col+1)+(row*N_col);		/* retval may be 1, 2 or 3*/
						}
					break;
					case 1:
						DIO_read(KEYPAD_PORT_IN,PIN3,data);
						if (LOW == *data)
						{
							retval = (col+1)+(row*N_col);		/* retval may be 4, 5 or 6*/	
						}
					break;
					case 2:
						DIO_read(KEYPAD_PORT_IN,PIN4,data);
						if (LOW == *data)
						{
							retval = (col+1)+(row*N_col);		/* retval may be 7, 8 or 9*/
						}
					break;
					default:
					break;
				
				}
			
			}
		
		}
		DIO_write(KEYPAD_PORT_OUT,PIN5,HIGH);
		DIO_write(KEYPAD_PORT_OUT,PIN6,HIGH);
		DIO_write(KEYPAD_PORT_OUT,PIN7,HIGH);
		return retval;
}