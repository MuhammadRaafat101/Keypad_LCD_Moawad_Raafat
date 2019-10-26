



#include"Task.h"
#include "LCD.h"
typedef enum
{
	SCREEN_NUM_1,
	SCREEN_NUM_2,
	SCREEN_QUESTIONS

}Enm_Screens_t ;

Enm_Screens_t Screen = SCREEN_NUM_1;


//static uint8_t lcd_g =0;
static uint8_t Pressed_key = 0;

uint8_t *question[6] =
{
	"First  one    ? ",
	"Second one    ? ",
	"Third  one    ? ",
	"Forth  one    ? ",
	"Fifth  one    ? "
};

uint8_t* Welcome_screen = "Press 1 to Start";
uint8_t* Options_screen = "1-Yes 2-No 3-Skp";

uint8_t i = 0;

static uint8_t Display_check=PENDING;
static uint8_t Goto_check=PENDING;
static uint8_t rowcol = 0;
void Keypad_100(void)
{
	static uint8_t check_num = 0;

			Pressed_key = KeyPad_getPressedKey();

			if (Pressed_key == 0)
			{
				PORTB |= 1<<PIN5;
			}
			else
			{
				PORTB &= ~(1<<PIN5);
				Display_check=PENDING;
				Goto_check=PENDING;
				rowcol = 0;
				i=2;
			}
}

void Task_2m(void)
{
	static uint8_t x=0;

//	Display_check = LCD_displayStr(question[i]);
	switch(Screen)
	{
		case SCREEN_NUM_1:
			if( Display_check == PENDING )
			{
				Display_check = LCD_displayStr(question[i]);
			}
			else if (Goto_check == PENDING && rowcol == 1)
			{
				Goto_check = LCD_gotoRawCol( 1 , 0 );
			}
			else
			{
				rowcol = 1;
			}
		break;



		case SCREEN_NUM_2:

		if( Display_check == PENDING )
		{
			Display_check = LCD_displayStr(Options_screen);

		}
		if (Display_check == COMPLETED)
		{
			Screen = SCREEN_QUESTIONS;
			Goto_check = PENDING;
			Display_check = COMPLETED;
			rowcol = 0;
		}



		break;



		case SCREEN_QUESTIONS:
			if (Goto_check == PENDING )
			{
				Goto_check = LCD_gotoRawCol( 0 , 0 );
			}
			else if( Display_check == PENDING && rowcol == 1)
			{
				Display_check = LCD_displayStr(question[i]);

			}

			else
			{
				rowcol = 1;
			}



		break;

		default:
		break;
	}


	//_delay_ms(1);

}
