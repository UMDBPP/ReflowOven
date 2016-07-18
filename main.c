#include <avr/io.h>
#include <avr/interrupt.h>

#include "System/clock.h"

void init();

int main(void) {
	init();

	for(;;) {
		// Do something
	}

	return 0; // Never reach
}

void init() {
	sei(); // Interrupts on initially

	clock_init();
}
