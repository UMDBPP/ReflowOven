/**
 * \file uart.c
 *
 * \brief USART0 in UART mode implementation
 *
 */ 

#include "drivers/uart.h"
#include <avr/io.h>

/*************************************************************************//**
Calls uart_transmit
  @brief Called when stdout is being printed to USART0 (this is set up at runtime)
  @param[in] var byte to transmit
  @param[in/out] *stream Pointer to a stdio.h FILE io stream
  @return Status
*****************************************************************************/
int uart_putchar_printf(char var, FILE *stream) {
	if (var == '\n') uart_transmit('\r');
	uart_transmit(var);
	return 0;
}

/*************************************************************************//**
  @brief Initializes USART0 in asynchronous UART mode, 8 bit data, 1 stop bit
  @param[in] desired baud rate (configuration values computed using F_CPU)
*****************************************************************************/
void uart_init(unsigned long baud){
	
	stdout = &uart_stdout; //make stdout print to USART0
	
	//Compute UBRR for baudrate setting
	unsigned short ubrr=(unsigned short)((F_CPU/(baud*16UL))-1);
	
	//Set BAUD rate.
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	
	/*Set frame format. 8 data bit(settings bits UCSZ00 and UCSZ01  UCSR0B), 1 stop bit(by default and need not to be worried about). 
	The UCSZ01:0 bits combined with the UCSZ02 bit in UCSR0B sets the number of data
	bits (Character Size) in the frame that the Receiver and Transmitter use. 
	If a change on frame format is needed, make sure to modify UCSR0B register above accordingly.
	See datasheet pg. 390.*/
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	
	//Enable receiver and transmitter. Enable the USART Receive Complete interrupt(RXCIE).
	//UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0));
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);//Enable RX/TX, no interrupts
}

/*************************************************************************//**
Transmits a byte
  @brief Transmits a byte via USART0
  @param[in] data byte to be transmitted
*****************************************************************************/
void uart_transmit(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0))); //Wait for the empty transmit buffer. (Waiting UDR0 to be empty.)
		UDR0 = data;			//store the data in the USART Data Register
}

/*************************************************************************//**
  @brief Receives a byte via USART0
  @return the received byte
*****************************************************************************/
unsigned char uart_receive(void){
	while (!(UCSR0A & (1 << RXC0))); //Do nothing until data have been received and is ready to be read from USART Data Register
	return UDR0;	//when data is ready to be received, return the content stored in the USART Data Register(UDR0.)
}

/*************************************************************************//**
  @brief Flushes out the USART0 receive buffer
*****************************************************************************/
void uart_flush(void){
	unsigned char dummy;
	while(UCSR0A & (1 << RXC0))
		dummy = UDR0;
}