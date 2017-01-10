CC=avr-gcc
OBJCOPY=avr-objcopy
PROGRAMMER=atmelice_isp
OPTLEVEL=-Os
CFLAGS=-c -I. $(OPTLEVEL) -ansi -pedantic-errors -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wall -Wextra -Wshadow -mmcu=atmega328p #-Werror
LFLAGS=-I. $(OPTLEVEL) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ansi -pedantic-errors -Wall -Wextra -Werror -mmcu=atmega328p #-Werror

all: main.o clock.o spi.o uart.o
	$(CC) $(LFLAGS) -Wl,-Map=Reflow.map,--cref main.o clock.o spi.o uart.o -o Reflow.elf
	$(OBJCOPY) -O ihex -R .eeprom Reflow.elf Reflow.hex

upload: Reflow.hex
	sudo avrdude -c $(PROGRAMMER) -p m328p -U flash:w:Reflow.hex

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clock.o: System/clock.c
	$(CC) $(CFLAGS) System/clock.c -o clock.o

spi.o: drivers/spi.c
	$(CC) $(CFLAGS) drivers/spi.c -o spi.o

uart.o: drivers/uart.c
	$(CC) $(CFLAGS) drivers/uart.c -o uart.o

clean:
	set -e
	rm *.o
	rm *.elf

purge: clean
	rm *.hex
	rm *.map

.PHONY: clean purge upload
