#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdint.h>
#include "config.h"

void clock_init(); /* Should be called at start of main() (or in some global init function) */

/* Usable userspace functions */
uint32_t clock_get_ms();
void clock_delay(uint32_t _delayTime); /* Delay time in ms. */
void clock_reset(); /* Reset the counter to start from 0. */

#endif /* __CLOCK_H__ */