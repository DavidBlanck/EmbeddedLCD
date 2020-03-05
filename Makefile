# David Blanck
# Makefile

delay.o: delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o

lcd.o: lcd.c delay.h
	avr-gcc -mmcu=atmega328p -c lcd.c -o lcd.o

main.o: main.c lcd.h delay.h
	avr-gcc -mmcu=atmega328p -c main.c -o main.o

main.elf: main.o lcd.o delay.o
	avr-gcc -mmcu=atmega328p main.o lcd.o delay.o -o main.elf

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

make install: main.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:main.hex:i

clean:
	rm -f *.o *.elf *.hex *.lst*
