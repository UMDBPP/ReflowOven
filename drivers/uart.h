/**
 * \file uart.h
 *
 * \brief USART0 in UART mode
 *
 */


#ifndef __USART0_H__
#define __USART0_H__

#include <stdio.h>
#include "config.h"

/* Function Prototypes */
int uart_putchar_printf(char var, FILE *stream);
void uart_init(unsigned long baud);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_flush(void);

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_printf, NULL, _FDEV_SETUP_WRITE); /* FILE handle for stdout */

#endif /* __USART0_H__ */