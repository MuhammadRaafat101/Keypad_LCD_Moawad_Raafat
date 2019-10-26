/*
 * Infotainment.c
 *
 * Created: 10/26/2019 12:16:52 PM
 * Author : M_Moawad
 */ 



#include"OS.h"
#include "LCD.h"
#include "keypad.h"

typedef enum 
{
	SCREEN_NUM_1,
	SCREEN_NUM_2,
	SCREEN_QUESTIONS
	
}Enm_Screens_t ;

Enm_Screens_t Screen = SCREEN_NUM_1;


void Toggle_LED0(void);
void Toggle_LED2(void);
void Task_2m(void);
void System_Init(void);
void Keypad_100(void);
void Question_task_10_sec (void);
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

int main()
{
	DDRB=0xFF;
	PORTB=0;

	OS_ConfigType Config={2,Timer0};
	OS_ConfigType* ConfigPtr=&Config;
	DIO_init();

// 	while(1)
// 	{
// 	Pressed_key = KeyPad_getPressedKey();
// 	if (Pressed_key == 0)
// 	{
// 		PORTB |= 1<<PIN5;
// 	}
// 	else
// 	{
// 		PORTB &= ~(1<<PIN5);
// 	}
//
// 	}


	OS_Init( ConfigPtr);


	OS_Creat_Task(1,System_Init, 0);

	OS_Creat_Task(2,Task_2m, 2);
	
	OS_Creat_Task(100,Keypad_100, 2);

	//OS_Creat_Task(2,System_Init, 0);
	//OS_Creat_Task(2,Toggle_LED2, 1);
	OS_Creat_Task(200,Keypad_100, 0);

	SREG|=(1<<7);

	OS_Run();
}



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
				//Display_check=PENDING;
				Goto_check=PENDING;
				rowcol = 0;
				i=2;
			}
}

void Task_2m(void)
{
	static uint8_t x=0;

	Display_check = LCD_displayStr(question[i]);
	/*switch(Screen)
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
*/
}

void Toggle_LED2(void)
{
}


void System_Init(void)
{

	LCD_init();
	/*	if(check==0)
	{
		check= LCD_init();
	}*/
}

void Question_task_10_sec (void)
{
// 	if (i < 6 )
// 	{
// 		i++;
// 		Display_check=PENDING;
// 		Goto_check=PENDING;
// 		rowcol = 0;
// 		
// 	}
	
}
