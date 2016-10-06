/*
 * Arduino.h
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <stm32f10x.h>
#include <system_stm32f10x.h>

#include <sys/cdefs.h>
#include <sys/types.h>
#include <pins_arduino.h>
#include <types.h>
#include <interrupts.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifdef __cplusplus
#include <Print.h>
#include <Printable.h>
#include <Stream.h>
#include <WCharacter.h>
#include <WMath.h>
#include <WString.h>
#include <uart.h>
#endif

#ifndef _BV
#define _BV(x) (1UL << (x))
#endif

#ifndef F_CPU
#define F_CPU SystemCoreClock
#endif

__BEGIN_DECLS

// Sketch

void setup(void);
void loop(void);

// Pin modes

#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP	2
#define INPUT_PULLDOWN	3
#define ANALOG			4
#define OPENDRAIN		5
#define OUTPUT_ALT		6
#define OPENDRAIN_ALT	7

void pinMode(uint8_t pin, uint8_t mode);

// Digital pin states

#define HIGH			1
#define LOW				0

uint8_t digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t state);

// Interrupts

#define FALLING			0x0c
#define RISING			0x08
#define CHANGE			0x10

typedef void (*isr_t)(void);

#define interrupts()	__enable_irq()
#define noInterrupts()	__disable_irq()
#define digitalPinToInterrupt(x)	(x)
void attachInterrupt(uint8_t pin, isr_t isr, uint8_t edge);
void detachInterrupt(uint8_t pin);

// Analog pin states

// Special channels for ADC
#define VREF			0xFE
#define TEMP			0xFF

uint16_t analogRead(uint8_t pin);
void analogWrite(uint8_t pin, uint16_t value);
void analogReadResolution(uint8_t bits);
void analogWriteResolution(uint8_t bits);

// Scheduling

void yield(void);
#define wait(cond) while (cond) yield()

// Timing

uint32_t millis(void);
uint32_t micros(void);

void delay(uint32_t time);
void delayMicroseconds(uint32_t time);

__END_DECLS

#endif /* ARDUINO_H_ */
