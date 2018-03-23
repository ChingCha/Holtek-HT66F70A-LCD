#include "HT66F70A.h"
#include "holtek_lcd.h"
#include <string.h>
// E = PE0 | RS = PE1 | R/W = GND | DATA = PD
#define LCM_EN			_pe0
#define LCM_ENC			_pec0
#define LCM_RS			_pe1
#define LCM_RSC			_pec1
#define LCM_DataPort	_pd
#define LCM_DataPortC	_pdc

void LCD_Init(void)
{
	GCC_DELAY(30000);
	LCD_CMD(0x33);
	LCD_CMD(0x32);
	LCD_CMD(0x28);
	GCC_DELAY(1000);
	LCD_CMD(0x0C);
	GCC_DELAY(1000);
	LCD_CMD(0x01);
	GCC_DELAY(1000);
	LCD_CMD(0x06);
	GCC_DELAY(10000);
	LCD_CMD(0x80);
	GCC_DELAY(10000);	
}
char LCD_BUSY(void)
{
   char busy;
   
   //LCM_RW = 1;
   LCM_RS = 0;
   LCM_EN = 1;
   GCC_DELAY(5);
   
   LCM_RSC = 0;
   LCM_ENC = 0;
   
   GCC_DELAY(5); 
   LCM_EN = 0; 
   return (busy);
}
void LCD_CMD(char cmd)
{ 
	LCM_EN = 0;
	LCM_DataPortC = 0;
	GCC_DELAY(5);
	//LCM_RW = 0;
	GCC_DELAY(5);
	LCM_DataPort = cmd;
	
	GCC_DELAY(5);
	LCM_EN = 1;
	GCC_DELAY(5);
	LCM_EN = 0;
	GCC_DELAY(5);
}
void LCD_DATA(char data1)
{
	LCM_RS = 1;
	GCC_DELAY(5);
	LCM_DataPort = data1;		
	GCC_DELAY(5);
	LCM_EN = 1;
	GCC_DELAY(5);
	LCM_EN = 0;
}
void LCD_Str(char addr1,char *str)
{
	LCD_CMD(addr1);
	while(*str !=0)
	{
		LCD_DATA(*str++);
	}
}
void LCD_Chr(char col,char chrx)
{
	LCD_CMD(col);         
	LCD_DATA(chrx);	                    
}