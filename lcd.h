/* David Blanck & Carl Yarwood
   lcd.c
*/

void pulseENABLE();
void write4bits( uint8_t bits );
void command( uint8_t cmd );
void lcdInit( uint8_t rs, uint8_t enable, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7 );
void lcdPutc( uint8_t c );
void lcdPuts( unsigned char *s );
void lcdClear();
void lcdHome();
void lcdCursorOn();
void lcdCursorOff();
