#include <avr/io.h>
#include <avr/power.h>
#include "drivers/spi.h"

#define MISO	B4
#define MOSI	B3
#define SCK		B5

static void init(void);

void spi_init()
{
	pinMode(SS, OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	pinPullup(MISO, PULLUP_ENABLE);
	//pinWrite(SS, HIGH);

	init();
	
	spi_disable();
}

static void init()
{
	SPCR = _BV(SPE)|_BV(MSTR);
	SPSR = _BV(SPI2X);
}

void spi_enable()
{
	power_spi_enable();
	init(); // Datasheet says to reinitialize after waking up
}

void spi_disable()
{
	power_spi_disable();
}

static inline bool chip_select()
{
	spi_enable();
	spiSelect();
	return true;
}

static inline bool chip_deselect(void)
{
	spiDeselect();
	spi_disable();
	return false;
}