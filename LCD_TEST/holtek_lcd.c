#include "HT66F70A.h"
#include "holtek_lcd.h"
#include <string.h>
// E = PE0 | RS = PE1 | R/W = GND | DATA = PD
#define LCD_EN			_pe0
#define LCD_ENC			_pec0
#define LCD_RS			_pe1
#define LCD_RSC			_pec1
//#define LCD_RW			_pe2
//#define LCD_RWC			_pec2
#define LCD_DataPort	_pd
#define LCD_DataPortC	_pdc

void LCD_Init(void)
{
	LCD_EN = 0;
	LCD_RS = 0;
	LCD_ENC = 0;
	LCD_RSC = 0;

}
void LCD_CMD(unsigned short RS,unsigned short cmd)
{ 
	LCD_DataPortC = 0;
	LCD_RS = RS;
	LCD_DataPort = cmd;
	LCD_EN = 1;
	_nop();
	LCD_EN = 0;
}

void DELAY_MS(unsigned short i)						
{	unsigned short j;
	for (j=0;j<i;j++) GCC_DELAY(1000);				//Delay i*10mS 
}