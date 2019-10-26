

#include"LCD.h"



static uint8_t Send_Command_Busy_Flag =0;
static uint8_t Send_Command_complete_Flag =0;
static uint8_t LCD_init_gurd=0;
/*static uint8_t LCD_Send_Character=0;*/


void LCD_init(void){
	/* set the control pins as output pins*/
	enum_status_t Status=PENDING;
	static uint8_t State=0;
	if(LCD_init_gurd == 0)
	{
		if(Send_Command_Busy_Flag == 0)
		{
			switch(State)
			{
			case 0 :
				DIRECTION_CTRL_PINS |=(1<<RS)|(1<<RW)|(1<<E);
				DIRECTION_DATA_PINS|=0xF0;
				State++;
				break;
			case 1:
				LCD_sendCommand(BITS_4_MODES);
				if(Send_Command_complete_Flag == 1)
				{
					Send_Command_complete_Flag=0;
					State++;
				}
				break;

			case 2 :
				LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
			//	LCD_Send_Character=1;
				if(Send_Command_complete_Flag == 1)
				{
					Send_Command_complete_Flag=0;
					State++;
				}
				break;
			case 3:
				LCD_sendCommand(CURSOR_OFF);
				if(Send_Command_complete_Flag == 1)
				{
					Send_Command_complete_Flag=0;
					State++;
				}
				break;
			case 4 :
				LCD_sendCommand(CLEAR_LCD);
				if(Send_Command_complete_Flag == 1)
				{
					Send_Command_complete_Flag=0;

					State++;
				}
				break;
			default :
				//OS_Delete_Task(LCD_init);
				LCD_init_gurd=1;
				Send_Command_Busy_Flag=1;
				//LCD_Send_Character=1;
				Status=COMPLETED ;
				break;
			}
		}
	}
	//return Status;
}

enum_status_t LCD_sendCommand(unit8 command){


	static uint8_t State=0;
	enum_status_t Status=PENDING;

	switch(State)
	{
	case 0:
		TAKE_FTCOMMAND(DATA_OUTPUT_PINS,command);		/*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS & 0x0F) | (command & 0xF0);*/
		Pin_clear(CTRL_OUTPUT_PINS  ,RS);
		Pin_clear(CTRL_OUTPUT_PINS ,RW);
		Pin_output(CTRL_OUTPUT_PINS  ,E);
		Pin_clear(CTRL_OUTPUT_PINS,E);
		State++;
		break;


	case 1:

		TAKE_SCCOMMAND(DATA_OUTPUT_PINS,command);  	  	/*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS&0x0F)|((command&0x0F)<<4);*/
		Pin_output(CTRL_OUTPUT_PINS  ,E);				/*start enabling again*/ /* Enable =1 */
		Pin_clear(CTRL_OUTPUT_PINS,E);
		State++;
		break;
	default :

		Send_Command_complete_Flag=1;
		State=0;
		Status=COMPLETED;
		break;
	}
	return Status;
}

/*
enum_status_t LCD_displayChar(uint8_t data){

	enum_status_t Status=PENDING;
	//static uint8_t LCD_Send_Character = 1;
	static uint8_t State=0;
	if (LCD_init_gurd == 1)
	{
	switch(State)
		{
		case 0 :
			TAKE_FTCOMMAND(DATA_OUTPUT_PINS,data);	wait tdpw to make enable =0
			Pin_output(CTRL_OUTPUT_PINS  ,RS);
			Pin_clear(CTRL_OUTPUT_PINS  ,RW);												 Enable =1
			Pin_output(CTRL_OUTPUT_PINS  ,E);	 wait 190 ns before sending command tpw-tdsw
			Pin_clear(CTRL_OUTPUT_PINS,E);
			State++;
			break;
		case 1 :

			TAKE_SCCOMMAND(DATA_OUTPUT_PINS,data);
			Pin_output(CTRL_OUTPUT_PINS ,E);
			Pin_clear(CTRL_OUTPUT_PINS,E);
			State++;

			break;

		default :
			Status=OK;
			State=0;
			//LCD_Send_Character=0;
			break;
		}
	}


	return Status;
}

*/

enum_status_t LCD_displayStr(uint8_t* data){

	enum_status_t Status=PENDING;
	static uint8_t index = 0;
	//static uint8_t LCD_Send_Character = 1;
	static uint8_t State=0;
	if (LCD_init_gurd == 1)
	{
		if(*(data+index) != '\0')
		{
			//d = *data;
			switch(State)
			{
			case 0 :
				TAKE_FTCOMMAND(DATA_OUTPUT_PINS,*(data+index));	/*wait tdpw to make enable =0 */
				Pin_output(CTRL_OUTPUT_PINS  ,RS);
				Pin_clear(CTRL_OUTPUT_PINS  ,RW);												/* Enable =1 */
				Pin_output(CTRL_OUTPUT_PINS  ,E);	/* wait 190 ns before sending command tpw-tdsw*/
				Pin_clear(CTRL_OUTPUT_PINS,E);
				State++;
				break;
			case 1 :

				TAKE_SCCOMMAND(DATA_OUTPUT_PINS,*(data+index));
				Pin_output(CTRL_OUTPUT_PINS ,E);
				Pin_clear(CTRL_OUTPUT_PINS,E);
				State++;

				break;

			default :
				State=0;

				index++;
				//LCD_Send_Character=0;
				break;
			}
		}
		else
		{
			//PORTB |= 1<<6;
			index = 0;
			Status=COMPLETED;
		}

	}


return Status;
}

enum_status_t LCD_gotoRawCol(unit8 row, unit8 col){
	unit8 address;
	enum_status_t Status=PENDING;
	switch(row){
		case 0:
		address=col;
		break;
		case 1:
		address=0x40+col;
	}
	
	Status = LCD_sendCommand(address|CURSOR_MoveToFirstLoc);
	
	return Status;
}



/*

enum_status_t LCD_displayString(const char *Str)
{
	enum_status_t Status=PENDING;
	uint8_t check =PENDING;

	if((*Str) != '\0')
		{
		check =LCD_displayChar(*Str);
		if(check==OK) Str++;

			Status=PENDING;
		}
	else if((*Str) == '\0')
	{
		Status=OK;
	}

	return Status;

}


void LCD_gotoRawCol(unit8 row, unit8 col){
	unit8 address;
	switch(row){
	case 0:
		address=col;
		break;
	case 1:
		address=0x40+col;
	}
	LCD_sendCommand(address|CURSOR_MoveToFirstLoc);

}





void LCD_IntToStr(int data){
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}


void LCD_displayStrRowCol(unit8 row,unit8 col, char *Str){
	unit8 address,i=0;
	switch(row){
	case 0:
		address=col;
		break;
	case 1:
		address=0x40+col;
	}
	LCD_sendCommand(address|CURSOR_MoveToFirstLoc);

	while((*Str) != '\0')
	{
		LCD_displayChar(Str[i]);
		Str++;
	}
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_LCD); //clear display
}



*/
