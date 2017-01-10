/*
 * @file config.h
 * 
 * @brief Configuration file for board-specific settings
 * 
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "util.h"

/* Chip Selects */
#define CS_SD   	C4
#define CS_T1		D7
#define CS_T2		B0
#define LCD_CS		C3

/* LCD */
#define LCD_DC		C2
#define LCD_RST		D4
#define LCD_BKLT	B2

/* Buttons */
#define BTNS		C0
#define SEL			D2

/* Other Peripherals */
#define THERM		C1
#define BUZZ		B1
#define HEAT1		D6
#define HEAT2		D5
#define FAN			D3

#ifndef F_CPU /* Build environments sometimes define this */
#define F_CPU	16000000UL
#endif

#endif /* __CONFIG_H__ */