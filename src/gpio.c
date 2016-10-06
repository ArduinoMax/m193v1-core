/*
 * gpio.c
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#include <system.h>
#include <Arduino.h>
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_exti.h>
#include <pins_arduino.h>
#include <stdlib.h>
#include <interrupts.h>

/*
 * #define INPUT			0
 * #define OUTPUT			1
 * #define INPUT_PULLUP		2
 * #define INPUT_PULLDOWN	3
 * #define ANALOG			4
 * #define OPENDRAIN		5
 * #define OUTPUT_ALT		6
 * #define OPENDRAIN_ALT	7
 */

static const GPIOMode_TypeDef pinMode_Mapping[] =
{
		GPIO_Mode_IN_FLOATING,
		GPIO_Mode_Out_PP,
		GPIO_Mode_IPU,
		GPIO_Mode_IPD,
		GPIO_Mode_AIN,
		GPIO_Mode_Out_OD,
		GPIO_Mode_AF_PP,
		GPIO_Mode_AF_OD
};

static GPIO_TypeDef *const port_Mapping[] =
{
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD
};

void GPIO_Configuration(void)
{
	for (uint8_t idx = 0; idx < 4; idx++)
	{
		GPIO_DeInit(port_Mapping[idx]);
	}
}

static isr_t isrVector[16] = {NULL};

void EXTI_Configuration(void)
{
	EXTI_DeInit();

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void pinMode(uint8_t pin, uint8_t mode)
{
	if (pin >= PIN_COUNT)
		return;
	if (mode >= 8)
		return;
	const pindesc_t *pindesc = &pins[pin];

	GPIO_InitTypeDef GPIO_InitStruct =
	{
			.GPIO_Pin = _BV(pindesc->pin),
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = pinMode_Mapping[mode]
	};
	GPIO_Init(port_Mapping[pindesc->port], &GPIO_InitStruct);
}

uint8_t getPinMode(uint8_t pin)
{
	if (pin >= PIN_COUNT)
		return INPUT;
	const pindesc_t *pindesc = &pins[pin];

	GPIO_TypeDef *GPIO = port_Mapping[pindesc->port];

	uint8_t modebits = (((pindesc->pin & 0x08) ? GPIO->CRH : GPIO->CRL) >> ((pindesc->pin & 0x07) << 2) & 0x0f);
	if (modebits & 0x03)
		modebits |= 0x03;
	modebits >>= 1;

	const uint8_t modebits_mapping[] = {ANALOG, OUTPUT, INPUT, OPENDRAIN, INPUT_PULLUP, OUTPUT_ALT, INPUT_PULLDOWN, OPENDRAIN_ALT};
	return modebits_mapping[modebits];
}

uint8_t digitalRead(uint8_t pin)
{
	if (pin >= PIN_COUNT)
		return 0;
	const pindesc_t *pindesc = &pins[pin];

	return GPIO_ReadInputDataBit(port_Mapping[pindesc->port], _BV(pindesc->pin));
}

void digitalWrite(uint8_t pin, uint8_t state)
{
	if (pin >= PIN_COUNT)
		return;
	const pindesc_t *pindesc = &pins[pin];

	stopPWM(pin);
	GPIO_WriteBit(port_Mapping[pindesc->port], _BV(pindesc->pin), state ? Bit_SET : Bit_RESET);
}

void attachInterrupt(uint8_t pin, isr_t isr, uint8_t edge)
{
	if (pin >= PIN_COUNT)
		return;
	const pindesc_t *pindesc = &pins[pin];

	GPIO_EXTILineConfig(pindesc->port, pindesc->pin);

	isrVector[pindesc->pin] = isr;

	EXTI_InitTypeDef EXTI_InitStruct =
	{
			.EXTI_Line = _BV(pindesc->pin),
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = edge,
			.EXTI_LineCmd = ENABLE,
	};
	EXTI_Init(&EXTI_InitStruct);
}

void detachInterrupt(uint8_t pin)
{
	if (pin >= PIN_COUNT)
		return;
	const pindesc_t *pindesc = &pins[pin];

	EXTI_InitTypeDef EXTI_InitStruct =
	{
			.EXTI_Line = _BV(pindesc->pin),
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Falling,
			.EXTI_LineCmd = DISABLE
	};
	EXTI_Init(&EXTI_InitStruct);

	isrVector[pindesc->pin] = NULL;
}

void EXTI_IRQHandler(uint8_t channel)
{
	EXTI_ClearITPendingBit(_BV(channel));

	isr_t isr = isrVector[channel];
	if (isr)
	{
		isr();
	}
}

void EXTI0_IRQHandler(void)
{
	EXTI_IRQHandler(0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_IRQHandler(1);
}

void EXTI2_IRQHandler(void)
{
	EXTI_IRQHandler(2);
}

void EXTI3_IRQHandler(void)
{
	EXTI_IRQHandler(3);
}

void EXTI4_IRQHandler(void)
{
	EXTI_IRQHandler(4);
}

void EXTI9_5_IRQHandler(void)
{
	for (uint8_t channel = 5; channel < 10; channel++)
	{
		if (EXTI_GetITStatus(_BV(channel)))
		{
			EXTI_IRQHandler(channel);
		}
	}
}

void EXTI15_10_IRQHandler(void)
{
	for (uint8_t channel = 10; channel < 16; channel++)
	{
		if (EXTI_GetITStatus(_BV(channel)))
		{
			EXTI_IRQHandler(channel);
		}
	}
}
