# David Blanck
# Makefile

delay.o: delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o

lcd.o: lcd.c delay.h
	avr-gcc -mmcu=atmega328p -c lcd.c -o lcd.o

lcd.elf: lcd.o delay.o
	avr-gcc -mmcu=atmega328p lcd.o delay.o -o lcd.elf

lcd.hex: lcd.elf
	avr-objcopy -j .text -j .data -O ihex lcd.elf lcd.hex

make install: lcd.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:lcd.hex:i

clean:
	rm -f *.o *.elf *.hex *.lst*
