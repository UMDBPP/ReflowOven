#include <avr/io.h>
#include <avr/power.h>
#include "drivers/spi.h"

#define MISO	B4
#define MOSI	B3
#define SCK		B5

static void init(void);

/*************************************************************************//**
  @brief Initializes the SPI hardware
  SPI starts out disabled
*****************************************************************************/
void spi_init(){
	pinMode(MOSI, OUTPUT);
	pinMode(SCK, OUTPUT);
	pinMode(MISO, INPUT);
	pinPullup(MISO, PULLUP_ENABLE);

	init();
	
	spi_disable();
}

/*************************************************************************//**
  @brief Sets some SPI hardware settings stuff
*****************************************************************************/
static void init(){
	SPCR = _BV(SPE)|_BV(MSTR);
	SPSR = _BV(SPI2X);
}

/*************************************************************************//**
  @brief Powers on SPI hardware
*****************************************************************************/
void spi_enable(){
	power_spi_enable();
	init(); /* Datasheet says to reinitialize after waking up */
}

/*************************************************************************//**
  @brief Powers off SPI hardware
*****************************************************************************/
void spi_disable(){
	power_spi_disable();
}