#include "HT66F70A.h"
#include "holtek_lcd.h"
#include "holtek_lcd.c"
void PAUSE(unsigned short i);
void main()
{	
	unsigned short i;
	LCD_Init();
	PAUSE(100);
	while(1)
	{
		LCD_CMD(0,0x80);
		for(i = 0;i < 16;i++)
		{
			LCD_CMD(1,0x31);
			PAUSE(100);
		}
		LCD_CMD(0,0xC0);
		for(i = 0;i < 16;i++)
		{
			LCD_CMD(1,0x32);
			PAUSE(100);
		}
	}
	
	
}
void PAUSE(unsigned short i)						
{	unsigned short j;
	for (j=0;j<i;j++) GCC_DELAY(10000);				//Delay i*10mS 
}