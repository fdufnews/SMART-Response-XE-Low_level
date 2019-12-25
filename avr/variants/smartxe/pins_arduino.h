/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

/*
	This version of pins_arduino.h is for the SMART Response XE
	fdufnews 2019/11/16 creation
	fdufnews 2019/12/2 added allocation of SRXE specific I/Os
	
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            26
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 26 : -1)
#define digitalPinHasPWM(p)         ((p) == 3 ||(p) == 4 ||(p) == 5 ||(p) == 8 ||(p) == 9 ||(p) == 19 ||(p) == 34 || (p) == 35)


// SPI interface
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)
const static uint8_t SS   = PIN_SPI_SS;
const static uint8_t MOSI = PIN_SPI_MOSI;
const static uint8_t MISO = PIN_SPI_MISO;
const static uint8_t SCK  = PIN_SPI_SCK;

// Signals for SPI devices
const static uint8_t FLASH_CS = 21;
const static uint8_t LCD_DC = 24;
const static uint8_t LCD_CS = 7;
const static uint8_t LCD_RST = 18;

// I2C interface
#define PIN_WIRE_SDA    (14)
#define PIN_WIRE_SCL    (15)
const static uint8_t SDA = PIN_WIRE_SDA;
const static uint8_t SCL = PIN_WIRE_SCL;

// Dedicated I/O
const static uint8_t LED = 10;
const static uint8_t BUZZER = 3;
const static uint8_t POWER_BUTTON = 20;
const static uint8_t VBATT = 26;


#define PIN_A0   (26)
#define PIN_A1   (27)
#define PIN_A2   (28)
#define PIN_A3   (29)
#define PIN_A4   (30)
#define PIN_A5   (31)
#define PIN_A6   (32)
#define PIN_A7   (33)
const static uint8_t A0 = PIN_A0;
const static uint8_t A1 = PIN_A1;
const static uint8_t A2 = PIN_A2;
const static uint8_t A3 = PIN_A3;
const static uint8_t A4 = PIN_A4;
const static uint8_t A5 = PIN_A5;
const static uint8_t A6 = PIN_A6;
const static uint8_t A7 = PIN_A7;

// A majority of the pins are NOT PCINTs, SO BE WARNED (i.e. you cannot use them as receive pins)
// Only pins available for RECEIVE (TRANSMIT can be on any pin):
// Pins: 7, 8, 9, 10, 11, 12, 13, 20

#define digitalPinToPCICR(p)    ( (((p) >= 7) && ((p) <= 13)) || \
                                  ((p) == 20) ? (&PCICR) : ((uint8_t *)0) )

#define digitalPinToPCICRbit(p) ( ((p) == 7) ? 1 : 0 ) 

#define digitalPinToPCMSK(p)    ( ((((p) >= 8) && ((p) <= 13)) || ((p) == 20)) ? (&PCMSK0) : \
                                ( ((p) == 7) ? (&PCMSK1) : \
                                ((uint8_t *)0) ) )

#define digitalPinToPCMSKbit(p) ( ((p) == 7) ? 0 : \
                                ( ((p) == 8) ? 4 : \
                                ( ((p) == 9) ? 7 : \
                                ( ((p) == 10) ? 6 : \
                                ( ((p) == 11) ? 5 : \
                                ( ((p) == 12) ? 3 : \
                                ( ((p) == 13) ? 1 : \
                                ( ((p) == 20) ? 2 : \
                                0 ) ) ) ) ) )

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&DDRB,
	NOT_A_PORT,
	(uint16_t)&DDRD,
	(uint16_t)&DDRE,
	(uint16_t)&DDRF,
	(uint16_t)&DDRG,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&PORTB,
	NOT_A_PORT,
	(uint16_t)&PORTD,
	(uint16_t)&PORTE,
	(uint16_t)&PORTF,
	(uint16_t)&PORTG,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	(uint16_t)&PINC,
	(uint16_t)&PIND,
	(uint16_t)&PINE,
	(uint16_t)&PINF,
	(uint16_t)&PING,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	// PORTLIST		
	// -------------------------------------------		
	PE	, // PE 0 ** 0 ** D0 / USART0_RX	
	PE	, // PE 1 ** 1 ** D1 / USART0_TX	
	PE	, // PE 2 ** 2 ** D2
	PE	, // PE 3 ** 3 ** D3 / PWM
	PE	, // PE 4 ** 4 ** D4 / PWM
	PE	, // PE 5 ** 5 ** D5 / PWM
	PE	, // PE 6 ** 6 ** D6
	PE	, // PE 7 ** 7 ** D7
	PB	, // PB 5 ** 8 ** D8 / PWM
	PB	, // PB 4 ** 9 ** D9 / PWM
	PB	, // PB 0 ** 10 ** D10 / SPI_SSN
	PB	, // PB 2 ** 11 ** D11 / SPI_MOSI
	PB	, // PB 3 ** 12 ** D12 / SPI_MISO
	PB	, // PB 1 ** 13 ** D13 / SPI_SCK
	PD	, // PD 1 ** 14 ** D14 / I2C_SDA
	PD	, // PD 0 ** 15 ** D15 / I2C_SCL
	PG	, // PG 0 ** 16 ** D16
	PG	, // PG 1 ** 17 ** D17
	PG	, // PG 2 ** 18 ** D18
	PG	, // PG 5 ** 19 ** D19 / PWM
	PD	, // PD 2 ** 20 ** D20 / USART1_RX
	PD	, // PD 3 ** 21 ** D21 / USART1_TX
	PD	, // PD 4 ** 22 ** D22
	PD	, // PD 5 ** 23 ** D23
	PD	, // PD 6 ** 24 ** D24
	PD	, // PD 7 ** 25 ** D25
	PF	, // PF 0 ** 26 ** A0 / D26
	PF	, // PF 1 ** 27 ** A1 / D27
	PF	, // PF 2 ** 28 ** A2 / D28
	PF	, // PF 3 ** 29 ** A3 / D29
	PF	, // PF 4 ** 30 ** A4 / D30	
	PF	, // PF 5 ** 31 ** A5 / D31	
	PF	, // PF 6 ** 32 ** A6 / D32	
	PF	, // PF 7 ** 33 ** A7 / D33
	PB	, // PB 6 ** 34 ** D34 / LED1 / LED / PWM
	PB	, // PB 7 ** 35 ** D35 / LED2 / PWM
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------		
	_BV( 0 )	, // PE 0 ** 0 ** USART0_RX	
	_BV( 1 )	, // PE 1 ** 1 ** USART0_TX	
	_BV( 2 )	, // PE 2 ** 2 ** D2
	_BV( 3 )	, // PE 3 ** 3 ** D3 / PWM
	_BV( 4 )	, // PE 4 ** 4 ** D4 / PWM
	_BV( 5 )	, // PE 5 ** 5 ** D5 / PWM
	_BV( 6 )	, // PE 6 ** 6 ** D6
	_BV( 7 )	, // PE 7 ** 7 ** D7
	_BV( 5 )	, // PB 5 ** 8 ** D8 / PWM
	_BV( 4 )	, // PB 4 ** 9 ** D9 / PWM
	_BV( 0 )	, // PB 0 ** 10 ** D10 / SPI_SSN
	_BV( 2 )	, // PB 2 ** 11 ** D11 / SPI_MOSI
	_BV( 3 )	, // PB 3 ** 12 ** D12 / SPI_MISO
	_BV( 1 )	, // PB 1 ** 13 ** D13 / SPI_SCK
	_BV( 1 )	, // PD 1 ** 14 ** D14 / I2C_SDA
	_BV( 0 )	, // PD 0 ** 15 ** D15 / I2C_SCL
	_BV( 0 )	, // PG 0 ** 16 ** D16
	_BV( 1 )	, // PG 1 ** 17 ** D17	
	_BV( 2 )	, // PG 2 ** 18 ** D18	
	_BV( 5 )	, // PG 5 ** 19 ** D19 / PWM
	_BV( 2 )	, // PD 2 ** 20 ** D20 / USART1_RX
	_BV( 3 )	, // PD 3 ** 21 ** D21 / USART1_TX
	_BV( 4 )	, // PD 4 ** 22 ** D22
	_BV( 5 )  	, // PD 5 ** 23 ** D23
	_BV( 6 )  	, // PD 6 ** 24 ** D24
	_BV( 7 )	, // PD 7 ** 25 ** D25
	_BV( 0 )	, // PF 0 ** 26 ** A0 / D26
	_BV( 1 )	, // PF 1 ** 27 ** A1 / D27
	_BV( 2 )	, // PF 2 ** 28 ** A2 / D28
	_BV( 3 )	, // PF 3 ** 29 ** A3 / D29
	_BV( 4 )	, // PF 4 ** 30 ** A4 / D30	
	_BV( 5 )	, // PF 5 ** 31 ** A5 / D31	
	_BV( 6 )	, // PF 6 ** 32 ** A6 / D32	
	_BV( 7 )	, // PF 7 ** 33 ** A7 / D33	
	_BV( 6 )	, // PB 6 ** 34 ** D34 / LED1 / LED / PWM
	_BV( 7 )	, // PB 7 ** 35 ** D35 / LED2 / PWM
};

// !!!
const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------	
	NOT_ON_TIMER	, // PE 0 ** 0 ** USART0_RX	
	NOT_ON_TIMER	, // PE 1 ** 1 ** USART0_TX	
	NOT_ON_TIMER	, // PE 2 ** 2 ** D2
	TIMER3A			, // PE 3 ** 3 ** D3 / PWM
	TIMER3B			, // PE 4 ** 4 ** D4 / PWM
	TIMER3C			, // PE 5 ** 5 ** D5 / PWM
	NOT_ON_TIMER	, // PE 6 ** 6 ** D6
	NOT_ON_TIMER	, // PE 7 ** 7 ** D7
	TIMER1A			, // PB 5 ** 8 ** D8 / PWM
	TIMER2A			, // PB 4 ** 9 ** D9 / PWM
	NOT_ON_TIMER	, // PB 0 ** 10 ** D10 / SPI_SSN
	NOT_ON_TIMER	, // PB 2 ** 11 ** D11 / SPI_MOSI
	NOT_ON_TIMER	, // PB 3 ** 12 ** D12 / SPI_MISO
	NOT_ON_TIMER	, // PB 1 ** 13 ** D13 / SPI_SCK
	NOT_ON_TIMER	, // PD 1 ** 14 ** D14 / I2C_SDA
	NOT_ON_TIMER	, // PD 0 ** 15 ** D15 / I2C_SCL
	NOT_ON_TIMER	, // PG 0 ** 16 ** D16
	NOT_ON_TIMER	, // PG 1 ** 17 ** D17	
	NOT_ON_TIMER	, // PG 2 ** 18 ** D18	
	TIMER0B			, // PG 5 ** 19 ** D19 / PWM
	NOT_ON_TIMER	, // PD 2 ** 20 ** D20 / USART1_RX
	NOT_ON_TIMER	, // PD 3 ** 21 ** D21 / USART1_TX
	NOT_ON_TIMER	, // PD 4 ** 22 ** D22
	NOT_ON_TIMER  	, // PD 5 ** 23 ** D23
	NOT_ON_TIMER  	, // PD 6 ** 24 ** D24
	NOT_ON_TIMER	, // PD 7 ** 25 ** D25
	NOT_ON_TIMER	, // PF 0 ** 26 ** A0 / D26
	NOT_ON_TIMER	, // PF 1 ** 27 ** A1 / D27
	NOT_ON_TIMER	, // PF 2 ** 28 ** A2 / D28
	NOT_ON_TIMER	, // PF 3 ** 29 ** A3 / D29
	NOT_ON_TIMER	, // PF 4 ** 30 ** A4 / D30	
	NOT_ON_TIMER	, // PF 5 ** 31 ** A5 / D31	
	NOT_ON_TIMER	, // PF 6 ** 32 ** A6 / D32	
	NOT_ON_TIMER	, // PF 7 ** 33 ** A7 / D33	
	TIMER1B			, // PB 6 ** 34 ** D34/ PWM
	TIMER1C			, // PB 7 ** 35 ** D35 / PWM
};	

#endif

#endif
