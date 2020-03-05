/*
  David Blanck & Carl Yarwood
  main.c
  A program which prints a message to the screen, iteratively changes the
  method, then prints a final message to the screen.
*/

#include <avr/io.h>
#include "delay.h"
#include "lcd.h"

void main( void ) {
  lcdInit(12, 13, 14, 15, 16, 17);
  lcdCursorOn();
  lcdPuts("Hello, world.");
  
  lcdHome();
  lcdCursorOn();
  lcdPutc('H');
  delay1ms(1000);
  lcdPutc('E');
  delay1ms(1000);
  lcdPutc('L');
  delay1ms(1000);
  lcdPutc('L');
  delay1ms(1000);
  lcdPutc('O');
  delay1ms(1000);
  lcdPutc(',');
  delay1ms(1000);
  lcdPutc(' ');
  delay1ms(1000);
  lcdPutc('W');
  delay1ms(1000);
  lcdPutc('O');
  delay1ms(1000);
  lcdPutc('R');
  delay1ms(1000);
  lcdPutc('L');
  delay1ms(1000);
  lcdPutc('D');
  delay1ms(1000);
  lcdPutc('!');
  delay1ms(1000);
  lcdClear();
  lcdCursorOff();

  lcdPuts("Goodbye, world.");
  while( 1 ) ;
}
