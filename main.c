#include <avr/io.h>
#include "delay.h"
#include "lcd.h"

void main( void ) {
  lcdInit(12, 13, 14, 15, 16, 17);
  lcdCursorOn();
  lcdPuts("Aloha, World!");
  delay1ms(2000);
  
  lcdHome();
  lcdPutc('W');
  lcdCursorOff();
  
  while( 1 ) ;
}
