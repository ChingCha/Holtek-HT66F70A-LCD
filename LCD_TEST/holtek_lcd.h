void LCD_Init(void);
char LCD_BUSY(void);
void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void LCD_Str(char addr1,char *str);
void LCD_Chr(char col,char chrx);