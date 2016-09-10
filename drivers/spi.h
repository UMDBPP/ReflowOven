#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "util.h"

void spi_init(void);
void spi_enable(void);
void spi_disable(void);

inline uint8_t spi_transfer(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); //Wait for existing transfer to finish
	SPDR = data;
	loop_until_bit_is_set(SPSR, SPIF);
	return SPDR;
}

inline void spi_transfer_nr(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); //Wait for existing transfer to finish
	SPDR = data;
	loop_until_bit_is_set(SPSR, SPIF);
}

inline void spit_transfer_noblock(uint8_t data){
	loop_until_bit_is_set(SPSR, SPIF); //Wait for existing transfer to finish
	SPDR = data;
}

#endif //SPI_H_