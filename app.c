

#include"OS.h"
#include "LCD.h"
#include "keypad.h"


void Toggle_LED0(void);
void Toggle_LED2(void);
void Task_2m(void);
void System_Init(void);
void Keypad_100(void);
//static uint8_t lcd_g =0;

uint8_t check=PENDING;
int main()
{
	DDRB=0xFF;
	PORTB=0;

	OS_ConfigType Config={2,Timer0};
	OS_ConfigType* ConfigPtr=&Config;
	DIO_init();

	OS_Init( ConfigPtr);


	OS_Creat_Task(1,System_Init, 0);

	OS_Creat_Task(1,Toggle_LED2, 1);



	//OS_Creat_Task(2,System_Init, 0);
	//OS_Creat_Task(2,Toggle_LED2, 1);
	OS_Creat_Task(100,Keypad_100, 2);

	SREG|=(1<<7);

	OS_Run();
}

void Toggle_LED0(void)
{


}
void Keypad_100(void)
{
	static uint8_t check_num = 0;
	static uint8_t num = 0;

	num = KeyPad_getPressedKey();

	if(num == 1)
	{

		PORTB |= (1<<6);

	}

	if(num == 2)
	{

		PORTB &= ~(1<<6);

	}
	if(num == 3)
	{

		PORTB |= (1<<6);

	}

	if(num == 4)
	{

		PORTB &= ~(1<<6);

	}

	if(num == 5)
	{

		PORTB |= (1<<6);

	}

	if(num == 6)
	{

		PORTB &= ~(1<<6);

	}

	if(num == 7)
	{

		PORTB &= ~(1<<6);

	}
	if(num == 8)
	{

		PORTB |= (1<<6);

	}

	if(num == 9)
	{

		PORTB &= ~(1<<6);

	}






}

void Task_2m(void)
{

}

void Toggle_LED2(void)
{



		if(check == PENDING)
		{
			check = LCD_displayStr("hahahaha :) ^_^");

		}else
		{
			PORTB |= 1<<PIN5;
		}
	//_delay_ms(1);

}


void System_Init(void)
{

	LCD_init();
	/*	if(check==0)
	{
		check= LCD_init();
	}*/
}

