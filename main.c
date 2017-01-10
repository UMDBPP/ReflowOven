#include <avr/io.h>
#include <avr/interrupt.h>

#include "System/clock.h"

void init();

int main(void) {
	init();

	while(1) {
		/* Do something */
	}

	return 0; /* Never reach */
}

void init() {
	sei(); /* enable interrupts */

	clock_init();
}
