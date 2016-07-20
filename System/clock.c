#include "clock.h"

#include <avr/interrupt.h>

// Internal variables not meant for outside access:
const uint32_t _usPerTimerOverflow = (64 * 256)/(F_CPU/1000000L);
volatile uint32_t _ms;
volatile uint8_t _msFrac;

// ISR on TC0 overflow:
ISR(TIMER0_OVF_vect) {
	uint32_t localMs = _ms;
	uint8_t localMsFrac = _msFrac;

	// Miros to millis; Note that these calcs are const, so precomputed by compiler.
	localMs += (_usPerTimerOverflow/1000);
	localMsFrac += ((_usPerTimerOverflow % 1000) >> 3);
	if(localMsFrac > 125) { // 125 = 1000 >> 3
		localMsFrac -= 125;
		localMs += 1;
	}

	_msFrac = localMsFrac;
	_ms = localMs;
}

void clock_init() {
	TCCR0B |= ((1 << CS01) | (1 << CS00)); // Prescalar: 64
	TIMSK0 |= (1 << TOIE0); // Interrupt enable
}

uint32_t clock_get_ms() {
	uint32_t localMs;
	uint8_t oldSREG = SREG;

	cli();
	localMs = _ms;
	SREG = oldSREG;

	return localMs;
}

void clock_delay(uint32_t _delayTime) {
	uint32_t delayUntil = clock_get_ms() + _delayTime;

	while(clock_get_ms() <= delayUntil) { } // do nothing until specified time.
}

void clock_reset() {
	uint8_t oldSREG = SREG;
	
	cli();
	_ms = 0;
	SREG = oldSREG;
}

