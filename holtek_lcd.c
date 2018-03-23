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
//-------------------------------------------------------------------
// CONSTANTS AND DEFINES
//-------------------------------------------------------------------
// LCD instruction set definitions

// Function set
#define DOT_5X10_OFF                    0x00
#define DOT_5X10_ON                     0x04
#define DUAL_LINE_OFF                   0x00
#define DUAL_LINE_ON                    0x08
#define BUS_8BIT_OFF                    0x00
#define BUS_8BIT_ON                     0x10
#define FUNCTION_SET(options)           lcdControl(0x20 | (options))

// Display clear
#define DISPLAY_CLEAR()                 lcdControl(0x01)

// Set display control
#define DISPLAY_CTRL_ON                 0x04
#define DISPLAY_CTRL_OFF                0x00
#define DISPLAY_CTRL_BLINK_ON           0x01
#define DISPLAY_CTRL_BLINK_OFF          0x00
#define DISPLAY_CTRL_CURSOR_ON          0x02
#define DISPLAY_CTRL_CURSOR_OFF         0x00
#define SET_DISPLAY_CTRL(options)       lcdControl(0x08 | (options))

// Set enter mode
#define INCREMENT_ON                    0x02
#define INCREMENT_OFF                   0x00
#define DISPLAY_SHIFT_ON                0x01
#define DISPLAY_SHIFT_OFF               0x00
#define SET_ENTER_MODE(options)         lcdControl(0x04 | (options))

// Set display control
#define SHITF_DISPLAY_ON                0x04
#define SHITF_DISPLAY_OFF               0x00
#define SHITF_RIGHT_ON                  0x02
#define SHITF_RIGHT_OFF                 0x00
#define SET_CURSOR_SHIFT(options)       lcdControl(0x10 | (options))

// Set Display Start Line
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))

// Set DD/CGRAM address
#define SET_DDRAM_ADDR(charIndex)       lcdControl(0x80 | (charIndex))
#define SET_GCRAM_CHAR(specIndex)       lcdControl(0x40 | (specIndex))

// LCD lines
#define LCD_LINE_COUNT                  2
#define LCD_LINE_LENGTH                 16

static char pLcdLineBuffer[LCD_LINE_LENGTH];

static void LCD_DATA(unsigned int data);
static void lcdControl(unsigned int command);
static void lcdWrite(unsigned int ch);
static void lcdWriteMany(char *pData, unsigned int count);
static void lcdWriteLine(unsigned int line, char *pText);
unsigned int pLedData;
static const char hex[] = 
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static void LCD_DATA(unsigned int data) 
{
	LCM_DataPort = data;
}
static void lcdControl(unsigned int command)
{   
    LCM_RS = 0;
    LCD_DATA(command);
    LCM_EN = 1;
    GCC_DELAY(2);
    LCM_EN = 0;
    GCC_DELAY(80);
    LCD_DATA(pLedData);
}
static void lcdWrite(unsigned int ch)
{
    LCM_RS = 1;
    LCD_DATA(ch);
    LCM_EN = 1;
    GCC_DELAY(2);
    LCM_EN = 0;
    GCC_DELAY(80);
    LCD_DATA(pLedData);
}
static void lcdWriteMany(char *pData, unsigned int count)
{
    while (count--)
    {
        lcdWrite(*(pData++));
    }
}
static void lcdWriteLine(unsigned int line, char *pText)
{
    if (line == 2)
    {
        SET_DISPLAY_LINE(LINE2);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1);
    }
    lcdWriteMany(pText, LCD_LINE_LENGTH);
}
void LcdInit(void)
{
    // Perform the initialization sequence
    LCM_RSC = 0;
	LCM_ENC = 0;
    LCM_EN = 0;
    GCC_DELAY(30000);

    FUNCTION_SET(BUS_8BIT_ON);
    GCC_DELAY(2000);
    FUNCTION_SET(BUS_8BIT_ON);
    GCC_DELAY(2000);
    FUNCTION_SET(BUS_8BIT_ON);
    GCC_DELAY(2000);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    GCC_DELAY(2000);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    GCC_DELAY(2000);
    SET_CURSOR_SHIFT(SHITF_DISPLAY_OFF);
    SET_ENTER_MODE(INCREMENT_ON);
    DISPLAY_CLEAR();
    GCC_DELAY(2000);
    // Clear the display
    LcdClear();
    SET_DISPLAY_CTRL(DISPLAY_CTRL_ON | DISPLAY_CTRL_BLINK_OFF | DISPLAY_CTRL_CURSOR_OFF);
}
void LcdClearLine(unsigned int line)
{
    unsigned int n;
    if (line == 2)
    {
        SET_DISPLAY_LINE(LINE2);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1);
    }
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
}
void LcdClear(void)
{
    unsigned int n;
    SET_DISPLAY_LINE(LINE1);
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
    SET_DISPLAY_LINE(LINE2);
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
}
unsigned int LcdGetLineLength(void)
{
    return LCD_LINE_LENGTH;
}
unsigned int LcdGetNumLines(void)
{
    return LCD_LINE_COUNT;
}
void LcdWriteChar(unsigned int line, unsigned int col, char text)
{
    if (line == 2)
    {
        SET_DISPLAY_LINE(LINE2 + col);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1 + col);
    }
    lcdWrite(text);
}
void LcdWriteString(unsigned int line, unsigned int col, char *pText)
{
    if (line == 2)
    {
        SET_DISPLAY_LINE(LINE2+col);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1+col);
    }
    lcdWriteMany(pText, strlen(pText));
}