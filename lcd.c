/* David Blanck
   lcd.c
   Implements functions for writing data to an LCD panel
*/


#include <avr/io.h>
#include "lcd.h"
#include "delay.h"

/*
#define CTRL_DDR DDRD
#define CTRL_PORT PORTD
#define RS (1<<PD6)
#define ENABLE (1<<PD7)

#define DATA_DDR DDRB
#define DATA_PORT PORTB
#define DB4 (1<<PB0)
#define DB5 (1<<PB1)
#define DB6 (1<<PB2)
#define DB7 (1<<PB3)


#define CTRL_DDR DDRD
#define CTRL_PORT PORTD

#define DATA_DDR DDRB
#define DATA_PORT PORTB


volatile uint8_t *CTRL_DDR;
volatile uint8_t *CTRL_PORT;
*/

uint8_t *RS_PORT;
uint8_t *RS_DDR;
uint8_t RS;
uint8_t *EN_PORT;
uint8_t *EN_DDR;
uint8_t ENABLE;

uint8_t *DB4_PORT;
uint8_t *DB4_DDR;
uint8_t DB4;
uint8_t *DB5_PORT;
uint8_t *DB5_DDR;
uint8_t DB5;
uint8_t *DB6_PORT;
uint8_t *DB6_DDR;
uint8_t DB6;
uint8_t *DB7_PORT;
uint8_t *DB7_DDR;
uint8_t DB7;

uint8_t* findPORTForPin(uint8_t pin) {
  if (pin == 1){
    return &PORTC;
  }
  else if(pin <= 13){
    return &PORTD;
  }
  else if( pin <= 19){
    return &PORTB;
  }
  else{
    return &PORTC;
  }
}

uint8_t* findDDRForPin(uint8_t pin) {
  if (pin == 1){
    return &DDRC;
  }
  else if(pin <= 13){
    return &DDRD;
  }
  else if( pin <= 19){
    return &DDRB;
  }
  else{
    return &DDRC;
  }
}

uint8_t findPinByteValue(uint8_t pin){
  if(pin == 1){
    return 1<<6;
  }
  else if( pin <= 6){
    return 1<<(pin-2);
  }
  else if( pin <= 13 ){
    return 1<<(pin-6);
  }
  else if( pin <= 19){
    return 1<<(pin-14);
  }
  else{
    return 1<<(pin-23);
  }
}
/*
  Writes a number of commands to initialize the LCD Panel.
*/
void lcdInit(uint8_t rs, uint8_t enable, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7) {
  // Save parameters for use elsewhere in the program
  
  RS_DDR = findDDRForPin(rs);
  RS_PORT = findPORTForPin(rs);
  RS = findPinByteValue(rs);

  EN_DDR = findDDRForPin(enable);
  EN_PORT = findPORTForPin(enable);
  ENABLE = findPinByteValue(enable);

  DB4_DDR = findDDRForPin(db4);
  DB4_PORT = findPORTForPin(db4);
  DB4 = findPinByteValue(db4);

  DB5_DDR = findDDRForPin(db5);
  DB5_PORT = findPORTForPin(db5);
  DB5 = findPinByteValue(db5);

  DB6_DDR = findDDRForPin(db6);
  DB6_PORT = findPORTForPin(db6);
  DB6 = findPinByteValue(db6);

  DB7_DDR = findDDRForPin(db7);
  DB7_PORT = findPORTForPin(db7);
  DB7 = findPinByteValue(db7);
  /*
  
  RS_DDR = &DDRD;
  RS_PORT = &PORTD;
  RS = 1<<6;

  EN_DDR = &DDRD;
  EN_PORT = &PORTD;
  ENABLE = 1<<7;

  DB4_DDR = &DDRB;
  DB4_PORT = &PORTB;
  DB4 = 1<<0;

  DB5_DDR = &DDRB;
  DB5_PORT = &PORTB;
  DB5 = 1<<1;

  DB6_DDR = &DDRB;
  DB6_PORT = &PORTB;
  DB6 = 1<<2;

  DB7_DDR = &DDRB;
  DB7_PORT = &PORTB;
  DB7 = 1<<3;
  */
  
  // Set all pins as outputs.
  *RS_DDR |= RS;
  *EN_DDR |= ENABLE;
  *DB4_DDR |= DB4;
  *DB5_DDR |= DB5;
  *DB6_DDR |= DB6;
  *DB7_DDR |= DB7;

  // Set RS and ENABLE low.
  *RS_PORT &= ~(RS);
  *EN_PORT &= ~(ENABLE);
  
  delay1ms( 50 ); // Wait 50ms for power on.
  write4bits( 0x03 ); // Init routine is to
  delay1ms( 5 ); // write 0x03 three times.
  write4bits( 0x03 );
  delay1ms( 1 );
  write4bits( 0x03 );
  delay1ms( 1 );
  write4bits( 0x02 ); // Choose 4-bit interface.
  command( 0x28 ); // 2 lines w/ 5x8 font.
  command( 0x0c ); // Display on, cursor off.
  command( 0x01 ); // Clear display.
  delay1ms( 2 ); // Wait 2ms for clear.
  command( 0x06 ); // Left-to-right text.
}



/*
  Pulse the ENABLE register
  This tells the LCD panel to read the next 4 bits
*/
void pulseENABLE( void ) {
  delay1us( 1 );
  *EN_PORT |= ENABLE; // Set ENABLE pin high
  delay1us( 1 );
  *EN_PORT &= ~ENABLE; // Set ENABLE pin low
  delay1us( 100 );
}

/*
  Sets each of the data port registers to the specified bit value
  Pulses ENABLE
*/
void write4bits( uint8_t bits ) {
  if( bits & 1 ) {
    *DB4_PORT |= DB4;
  }
  else {
    *DB4_PORT &= ~DB4;
  }
  
  if( bits & 2 ) {
    *DB5_PORT |= DB5;
  }
  else {
    *DB5_PORT &= ~DB5;
  }
  
  if( bits & 4 ) {
    *DB6_PORT |= DB6;
  }
  else {
    *DB6_PORT &= ~DB6;
  }
  
  if( bits & 8 ) {
    *DB7_PORT |= DB7;
  }
  else {
    *DB7_PORT &= ~DB7;
  }
  pulseENABLE();
}

/*
  Writes cmd to LCD Panel as a command
*/
void command( uint8_t cmd ) {
  *RS_PORT &= ~RS;
  write4bits( cmd>>4 );
  write4bits( cmd );
}


/*
  Writes cmd to LCD Panel as data
*/
void data( uint8_t c ) {
  *RS_PORT |= RS; // RS pin is high for data
  write4bits( c>>4 );
  write4bits( c );
}

void lcdPuts( unsigned char *s ) {
  while( *s ) data( *s++ );
}


void main( void ) {
  lcdInit(12, 13, 14, 15, 16, 17);
  lcdPuts("big hairy balls or something"  );
  while( 1 ) ;
}
