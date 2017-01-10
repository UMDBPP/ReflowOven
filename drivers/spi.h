#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "util.h"

void spi_init(void);
void spi_enable(void);
void spi_disable(void);

__inline__ uint8_t spi_transfer(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); /* Wait for existing transfer to finish */
	SPDR = data;
	loop_until_bit_is_set(SPSR, SPIF);
	return SPDR;
}

__inline__ void spi_transfer_nr(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); /* Wait for existing transfer to finish */
	SPDR = data;
	loop_until_bit_is_set(SPSR, SPIF);
}

__inline__ void spit_transfer_noblock(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); /* Wait for existing transfer to finish */
	SPDR = data;
}

#endif /* __SPI_H__ */