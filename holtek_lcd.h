void LcdInit(void);
void LcdClear(void);
unsigned int LcdGetLineLength(void);
unsigned int LcdGetNumLines(void);
void LcdWriteChar(unsigned int line, unsigned int col, char text);
void LcdWriteString(unsigned int line, unsigned int col, char *text);