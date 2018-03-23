#include "HT66F70A.h"
#include "holtek_lcd.h"
#include "holtek_lcd.c"
void PAUSE(unsigned short i);
void main()
{	
	LCD_Init();
	PAUSE(100);
	LCD_Str(0x80, "ABCDEF");
	PAUSE(1000);
}
void PAUSE(unsigned short i)						
{	unsigned short j;
	for (j=0;j<i;j++) GCC_DELAY(10000);				//Delay i*10mS 
}