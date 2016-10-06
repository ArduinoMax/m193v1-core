/*
 * SysTick.c
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#include <system.h>
#include <stm32f10x.h>
#include <interrupts.h>

#define SYSTICK_IRQ_PERIOD_US		(100)
#define SYSTICK_COUNTS_PER_PERIOD	(SystemCoreClock / 1000000 * SYSTICK_IRQ_PERIOD_US)

static volatile uint32_t millis_counter = 0;
static volatile uint32_t micros_counter = 0;

void SysTick_Configuration(void)
{
	SysTick_Config(SYSTICK_COUNTS_PER_PERIOD);
}

void SysTick_Handler(void)
{
	micros_counter += SYSTICK_IRQ_PERIOD_US;
	if (micros_counter >= 1000)
	{
		millis_counter++;
		micros_counter -= 1000;
	}
}

void __attribute__((weak)) yield(void) {}

uint32_t millis(void)
{
	__disable_irq();
	uint32_t ms = millis_counter;
	__enable_irq();

	return ms;
}

uint32_t micros(void)
{
	__disable_irq();
	uint32_t ms = millis_counter;
	uint32_t us = micros_counter;
	uint32_t count = SysTick->VAL;
	__enable_irq();

	return ms * 1000 + us + (SYSTICK_COUNTS_PER_PERIOD - count) / (SystemCoreClock / 1000000);
}

void delay(uint32_t time)
{
	int32_t end = (int32_t)(millis() + time);
	wait(end - (int32_t)millis() >= 0);
}

void delayMicroseconds(uint32_t time)
{
	int32_t end = (int32_t)(micros() + time);
	wait(end - (int32_t)micros() >= 0);
}
