#include "clock.h"

#include <avr/interrupt.h>

/* Internal variables not meant for outside access: */
static volatile uint32_t _ms;

void clock_init() {
	TCNT0 = 0;
	TCCR0A |= (1 << WGM01); /* CTC mode */
	TCCR0B |= (1 << CS01) | (1 << CS00); /* Prescalar: 64 */
	OCR0A = 250; /* 0.001s * 16MHz / 64 */
	TIMSK0 |= (1 << OCIE0A); /* Interrupt enable */
}

/* return how many ms have passed since execution start */
uint32_t clock_get_ms() {
	uint32_t local_ms;
	uint8_t old_SREG = SREG;
	cli();
	local_ms = _ms;
	SREG = old_SREG;
	return local_ms;
}

/* wait for _delay_time milliseconds */
void clock_delay(uint32_t _delay_time) {
	uint32_t delay_until = clock_get_ms() + _delay_time;
	while (clock_get_ms() <= delay_until);
}

/* reset ms counter to 0 */
void clock_reset() {
	uint8_t old_SREG = SREG;
	cli();
	_ms = 0;
	SREG = old_SREG;
}

/* ISR on TC0 overflow: */
ISR(TIMER0_COMPA_vect) {
	_ms++;
}
