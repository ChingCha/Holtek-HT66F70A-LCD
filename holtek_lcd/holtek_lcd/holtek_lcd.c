/*#include "HT66F50.h"
#define LCD_EN			_pe0
#define LCD_ENC			_pec0
#define LCD_RS			_pe1
#define LCD_RSC			_pec1

#define LCD_DataPort	_pd
#define LCD_DataPortC	_pdc
void LCD_CMD(unsigned short lcmd);
void LCD_Init(void);
void LCD_WRITE(unsigned short data);
void main()
{
	LCD_Init();
	LCD_CMD(0x80);
	LCD_WRITE(0x31);
	while(1)
	{
		LCD_CMD(0x80);
		LCD_WRITE(0x31);
		GCC_DELAY(100000);
		LCD_CMD(0xC0);
		LCD_WRITE(0x32);
		GCC_DELAY(100000);
	}
}

void LCD_CMD(unsigned short cmd)
{
	LCD_RS = 0;
	LCD_DataPort = cmd;
	LCD_EN = 1;
	GCC_DELAY(40);
	LCD_EN = 0;
	GCC_DELAY(40);
	cmd <<= 4;
	LCD_DataPort = cmd;
	GCC_DELAY(40);
	LCD_EN = 0;
	GCC_DELAY(40);
}
void LCD_Init(void)
{
	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RSC = 0;
	LCD_ENC = 0;
	LCD_DataPortC = 0;
	GCC_DELAY(50000);
	LCD_CMD(0x28);
	LCD_CMD(0x0F);
	LCD_CMD(0x06);
	LCD_CMD(0x01);
	GCC_DELAY(100000);
}
void LCD_WRITE(unsigned short data)
{
	LCD_RS = 1;
	LCD_DataPort = data;
	LCD_EN = 1;
	GCC_DELAY(40);
	LCD_EN = 0;
	GCC_DELAY(40);
	data <<= 4;
	LCD_DataPort = data;
	GCC_DELAY(40);
	LCD_EN = 0;
	GCC_DELAY(40);
}*/
// PROGRAM	: 5-6.c										   2011.0522
// FUNCTION	: 20*2 LCM Contrl Demo Program 		   By Steven
#include	"HT66F50.h"
#define LCM_EN			_pe0
#define LCM_ENC			_pec0
#define LCM_RS			_pe1
#define LCM_RSC			_pec1
#define LCM_RW			_pe2
#define LCM_RWC			_pec2
#define LCM_DataPort	_pd
#define LCM_DataPortC	_pdc
void LCMInit(void);
unsigned short LCMWrite(unsigned char, unsigned char);
void PAUSE(unsigned short);
void main()
{	unsigned short i;
	LCMInit();				                     //LCM Initialization
	while(1)
	{	
		LCMWrite(0,0x01);
		PAUSE(100);
		LCMWrite(0,0x80);						      //Clear LCM Display						
		for(i=0;i<16;i++)
		{	LCMWrite(1,0x31); PAUSE(10);        //Dispay "1"
		}
		LCMWrite(0,0xC0);					         //Set Line 2, Position 0
		for(i=0;i<16;i++) 
		{	LCMWrite(1,0x32); PAUSE(10);	      //Dispay "2"
		}
		PAUSE(100);  
	}
}
void LCMInit(void)
{	LCM_EN=0; LCM_RW=0; LCM_RS=0;	            //Clear EN/RW/RS Pin
	LCM_ENC=0; LCM_RWC=0; LCM_RSC=0;	         //Config EN/RW/RS O/PAUSE
	GCC_DELAY(50000);							         //LCM Power-On Time
	LCMWrite(0,0x28);							      //COMD:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);						         //COMD:Display/Cursor Blinking On
	LCMWrite(0,0x06);							      //COMD:Increment, Not Shift
	LCMWrite(0,0x01);							      //COMD:Clear LCM Display
}
unsigned short LCMWrite(unsigned char DCFlag, unsigned char CD)
{	unsigned short BusyAC;
	LCM_DataPortC=0;								   //Config Port as O/P Mode
	LCM_RW=0;										   //RW=0 (Write)
	LCM_RS=DCFlag;									   //Set RS State By DCFlag
	LCM_DataPort=CD;								   //Sent Command or Data
	LCM_EN=1; _nop(); LCM_EN=0;			      //EN=1
	LCM_DataPort= CD << 4;								   //Sent Command or Data
	LCM_EN=1; _nop(); LCM_EN=0;			      //EN=1
	return BusyAC;	
}
void PAUSE(unsigned short i)						
{	unsigned short j;
	for (j=0;j<i;j++) GCC_DELAY(10000);				//Delay i*10mS 
}