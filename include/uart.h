/*
 * uart.h
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include <HardwareSerial.h>
#include <Arduino.h>
#include <stm32f10x.h>
#include <core_cm3.h>
#include <stm32f10x_usart.h>
#include <RingBuffer.h>

#ifdef __cplusplus

enum {
	RCC_APB2Periph,
	RCC_APB1Periph
};

enum {
	Mode_8N1 = USART_Parity_No,
	Mode_8E1 = USART_Parity_Even,
	Mode_8O1 = USART_Parity_Odd
};

class UART_STM32 : public HardwareSerial
{
protected:
	USART_TypeDef *USART;
	IRQn_Type IRQn;
	uint8_t RxPin;
	uint8_t TxPin;
	uint8_t RCC_APBIdent;
	uint32_t RCC_Periph;
	RingBuffer RxBuffer;
	RingBuffer TxBuffer;

public:
	UART_STM32(USART_TypeDef *USART, IRQn_Type IRQn, uint8_t RCC_APBIdent, uint32_t RCC_Periph, uint8_t RxPin, uint8_t TxPin);
	void begin(const uint32_t baudrate);
	void begin(const uint32_t baudrate, const uint16_t mode);
	void end(void);
	int available(void);
	int availableForWrite(void);
	int peek(void);
	int read(void);
	void flush(void);
	size_t write(const uint8_t c);
	using Print::write;

	void interrupt(void);

	operator bool() { return true; };
};

extern UART_STM32 Serial;
extern UART_STM32 Serial1;
extern UART_STM32 Serial2;

#endif

#endif /* INCLUDE_UART_H_ */
