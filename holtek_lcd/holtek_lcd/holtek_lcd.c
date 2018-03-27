#include	"HT66F50.h"
#include <string.h>
#define LCD_EN			_pe0
#define LCD_ENC			_pec0
#define LCD_RS			_pe1
#define LCD_RSC			_pec1
#define LCD_RW			_pe2
#define LCD_RWC			_pec2
#define LCD_DataPort	_pd
#define LCD_DataPortC	_pdc
void LCD_Init(void);
unsigned short LCD_Write(unsigned char, unsigned char);
void PAUSE(unsigned short);
static void Str_To_Lcd(char *pData, unsigned int count);
void Lcd_Write_String(unsigned int line, unsigned int col, char *pText);
void Lcd_Clear(void);
void Lcd_Write_Char(unsigned int line, unsigned int col, char Text);
void main()
{	unsigned short i;
	LCD_Init();
	while(1)
	{	
		Lcd_Clear();
		PAUSE(100);
		char c = 'K';					
		for(i=0;i<16;i++)
		{	Lcd_Write_String(1,i,"S"); PAUSE(10);
		}
		for(i=0;i<16;i++) 
		{	Lcd_Write_Char(2,i,c); PAUSE(10);
		}
		PAUSE(100);  
	}
}
void LCD_Init(void)
{	LCD_EN=0; LCD_RW=0; LCD_RS=0;	            //Clear EN/RW/RS Pin
	LCD_ENC=0; LCD_RWC=0; LCD_RSC=0;	         //Config EN/RW/RS O/PAUSE
	GCC_DELAY(50000);							         //LCM Power-On Time
	LCD_Write(0,0x28);
	LCD_Write(0,0x08);						         //COMD:Display/Cursor Blinking On
	LCD_Write(0,0x06);							      //COMD:Increment, Not Shift
	LCD_Write(0,0x01);							      //COMD:Clear LCM Display
}
unsigned short LCD_Write(unsigned char DCFlag, unsigned char CD)
{	
	LCD_DataPortC=0;								   //Config Port as O/P Mode
	LCD_RW=0;										   //RW=0 (Write)
	LCD_RS=DCFlag;									   //Set RS State By DCFlag
	LCD_DataPort=CD;								   //Sent Command or Data
	LCD_EN=1; _nop(); LCD_EN=0;			      //EN=1
	LCD_DataPort= CD << 4;								   //Sent Command or Data
	LCD_EN=1; _nop(); LCD_EN=0;			      //EN=1	
}
void PAUSE(unsigned short i)						
{	unsigned short j;
	for (j=0;j<i;j++) GCC_DELAY(10000);				//Delay i*10mS 
}

static void Str_To_Lcd(char *pData, unsigned int count)
{
    while (count--)
    {
        LCD_Write(1,*(pData++));
    }
}
void Lcd_Write_String(unsigned int line, unsigned int col, char *pText)
{
	if(line == 1) 	LCD_Write(0,0x80 + col);
	if(line == 2) 	LCD_Write(0,0xC0 + col);
	Str_To_Lcd(pText, strlen(pText));
}
void Lcd_Clear(void)
{
	LCD_Write(0,0x01);
}
void Lcd_Write_Char(unsigned int line, unsigned int col, char Text)
{
	if(line == 1) 	LCD_Write(0,0x80 + col);
	if(line == 2) 	LCD_Write(0,0xC0 + col);
	LCD_Write(1,Text);
}