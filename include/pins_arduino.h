/*
 * pins_arduino.h
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#ifndef INCLUDE_PINS_ARDUINO_H_
#define INCLUDE_PINS_ARDUINO_H_

#include <stm32f10x.h>
#include <sys/cdefs.h>
#include <stddef.h>

#define PIN_COUNT	29

typedef struct
{
	uint8_t port;
	uint8_t pin;
	ADC_TypeDef *adc;
	uint32_t adchannel;
	TIM_TypeDef *timer;
	uint32_t pwmchannel;
} pindesc_t;

__BEGIN_DECLS

extern const pindesc_t pins[];

/* Pin map:
 *
 * Pin		Digital	Analog	Alt		Alt2	PWM		ADC
 *
 * PA0		D15				WAKEUP
 * PA1		D19		A1						T2/2	A1/1
 * PA2		D18		A0		TX1				T2/3	A1/2
 * PA3		D20		A2		RX1				T2/4	A1/3
 * PA4		D21		A3		NSS0					A1/4
 * PA5		D24		A6		SCK0					A2/5
 * PA6		D25		A7		MOSI0					A2/6
 * PA7		D26		A8		MISO0					A2/7
 * PA8		D6				CKO				T1/1
 * PA9		D1				TX0				T1/2
 * PA10		D0				RX0				T1/3
 *
 * PB0		D22		A4						T3/3	A1/8
 * PB1		D23		A5						T3/4	A1/9
 * PB2		D13
 * PB4		D7								T3/1
 * PB5		D8								T3/2
 * PB6		D9								T4/1
 * PB7		D10								T4/2
 * PB8		D16				SCL0	CANRX
 * PB9		D17				SDA0	CANTX
 * PB10		D12				SCL1	TX2
 * PB11		D11				SDA1	RX2
 * PB12		D2				NSS1
 * PB13		D3				SCK1
 * PB14		D4				MISO1
 * PB15		D5				MOSI1
 *
 * PC13		D14				LED
 *
 * PA11		N/A				UD-
 * PA12		N/A				UD+
 * PA13		N/A				TMS
 * PA14		N/A				TCK
 * PA15		N/A				TDI
 * PB3		N/A				TDO
 * PC1		N/A				HSE-XOUT
 * PC14		N/A				LSE-XIN
 * PC15		N/A				LSE_XOUT
 * PD0		N/A				HAE-XIN
 */

// ADC pins

#define A0			18
#define A1			19
#define A2			20
#define A3			21
#define A4			22
#define A5			23
#define A6			24
#define A7			25
#define A8			26

// Board peripherals

#define LED			14
#define WAKEUP		15

// I2C

#define SCL0		16
#define SDA0		17

#define SCL1		12
#define SDA1		11

// SPI

#define NSS0		21
#define SCK0		22
#define MOSI0		23
#define MISO0		24

#define NSS1		2
#define SCK1		3
#define MOSI1		5
#define MISO1		4

// UART

#define RX0			0
#define TX0			1

#define RX1			20
#define TX1			18

#define RX2			11
#define TX2			12

// USB

#define UDM			27
#define UDP			28

__END_DECLS

#endif /* INCLUDE_PINS_ARDUINO_H_ */
