/*
 * uart.cpp
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#include <uart.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include <core_cm3.h>
#include <pins_arduino.h>
#include <interrupts.h>

UART_STM32::UART_STM32(USART_TypeDef *USART, IRQn_Type IRQn, uint8_t RCC_APBIdent, uint32_t RCC_Periph, uint8_t RxPin, uint8_t TxPin)
{
	this->USART = USART;
	this->IRQn = IRQn;
	this->RCC_APBIdent = RCC_APBIdent;
	this->RCC_Periph = RCC_Periph;
	this->RxPin = RxPin;
	this->TxPin = TxPin;
	this->RxBuffer = RingBuffer();
	this->TxBuffer = RingBuffer();
}

void UART_STM32::begin(const uint32_t baudrate)
{
	begin(baudrate, Mode_8N1);
}

void UART_STM32::begin(const uint32_t baudrate, const uint16_t mode)
{
	if (RCC_APBIdent == RCC_APB1Periph)
	{
		RCC_APB1PeriphClockCmd(RCC_Periph, ENABLE);
	}
	else
	{
		RCC_APB2PeriphClockCmd(RCC_Periph, ENABLE);
	}

	USART_DeInit(USART);

	pinMode(RxPin, INPUT_PULLUP);
	pinMode(TxPin, OUTPUT_ALT);

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = baudrate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = mode;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART, &USART_InitStruct);
	USART_ITConfig(USART, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(IRQn);

	USART_Cmd(USART, ENABLE);
}

void UART_STM32::end(void)
{
	USART_Cmd(USART, DISABLE);

	NVIC_DisableIRQ(IRQn);

	pinMode(RxPin, INPUT);
	pinMode(TxPin, INPUT);

	USART_DeInit(USART);
}

void UART_STM32::interrupt(void)
{
	if (USART_GetFlagStatus(USART, USART_FLAG_RXNE))
	{
		USART_ClearFlag(USART, USART_FLAG_RXNE);
		RxBuffer.putch(USART_ReceiveData(USART));
	}

	if (USART_GetFlagStatus(USART, USART_FLAG_TXE))
	{
		int ch = TxBuffer.getch();
		if (ch >= 0)
		{
			USART_SendData(USART, ch & 0xff);
		}
		else
		{
			USART_ITConfig(USART, USART_IT_TXE, DISABLE);
		}
	}
}

int UART_STM32::available(void)
{
	return RxBuffer.flen();
}

int UART_STM32::availableForWrite(void)
{
	return SERIAL_BUFFER_SIZE - TxBuffer.flen();
}

int UART_STM32::read(void)
{
	return RxBuffer.getch();
}

int UART_STM32::peek(void)
{
	return RxBuffer.peekch();
}

void UART_STM32::flush(void)
{
	wait(TxBuffer.flen());
	wait(!USART_GetFlagStatus(USART, USART_IT_TXE));
}

size_t UART_STM32::write(uint8_t ch)
{
	wait(TxBuffer.putch(ch) < 0);
	USART_ITConfig(USART, USART_IT_TXE, ENABLE);

	return 0;
}

UART_STM32 Serial(USART1, USART1_IRQn, RCC_APB2Periph, RCC_APB2Periph_USART1, RX0, TX0);
UART_STM32 Serial1(USART2, USART2_IRQn, RCC_APB1Periph, RCC_APB1Periph_USART2, RX1, TX1);
UART_STM32 Serial2(USART3, USART3_IRQn, RCC_APB1Periph, RCC_APB1Periph_USART3, RX2, TX2);

void USART1_IRQHandler(void)
{
	Serial.interrupt();
}

void USART2_IRQHandler(void)
{
	Serial1.interrupt();
}

void USART3_IRQHandler(void)
{
	Serial2.interrupt();
}
