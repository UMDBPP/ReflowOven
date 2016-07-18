CC=avr-gcc
OBJCOPY=avr-objcopy
PROGRAMMER=atmelice_isp
OPTLEVEL=-Os
CFLAGS=-c -I. $(OPTLEVEL) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wall -Wextra -DF_CPU=16000000 -mmcu=atmega328p
LFLAGS=-I. $(OPTLEVEL) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wextra -DF_CPU=16000000 -mmcu=atmega328p

all: main.o clock.o
	$(CC) $(LFLAGS) -Wl,-Map=Reflow.map,--cref main.o clock.o -o Reflow.elf
	$(OBJCOPY) -O ihex -R .eeprom Reflow.elf Reflow.hex

upload: Reflow.hex
	sudo avrdude -c $(PROGRAMMER) -p m328p -U flash:w:Reflow.hex

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clock.o: System/clock.c
	$(CC) $(CFLAGS) System/clock.c -o clock.o

clean:
	rm *.elf
	rm *.o

purge: clean
	rm *.hex
	rm *.map

.PHONY: clean purge upload
