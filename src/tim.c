/*
 * tim.c
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#include <system.h>
#include <stm32f10x_tim.h>

void TIM_Configuration(void)
{
	static TIM_TypeDef *const timers[] = {TIM1, TIM2, TIM3, TIM4};
	for (uint8_t idx = 0; idx < 4; idx++)
	{
		TIM_TypeDef *TIM = timers[idx];

		TIM_DeInit(TIM);
		TIM_Cmd(TIM, ENABLE);
		TIM_ARRPreloadConfig(TIM, ENABLE);
	}

	analogWriteResolution(8);
}

void analogWriteResolution(uint8_t bits)
{
	analogSetMaximumValue((bits == 16) ? 0xffff : (1 << bits) - 1);
}

void analogSetMaximumValue(uint16_t value)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct =
	{
			.TIM_Prescaler = 0,
			.TIM_CounterMode = TIM_CounterMode_Up,
			.TIM_Period = value,
			.TIM_ClockDivision = TIM_CKD_DIV1,
			.TIM_RepetitionCounter = 0
	};

	static TIM_TypeDef *const timers[] = {TIM1, TIM2, TIM3, TIM4};
	for (uint8_t idx = 0; idx < 4; idx++)
	{
		TIM_TypeDef *TIM = timers[idx];
		TIM_TimeBaseInit(TIM, &TIM_TimeBaseStruct);
	}
}

void analogWrite(uint8_t pin, uint16_t value)
{
	if (pin >= PIN_COUNT)
		return;
	const pindesc_t *pindesc = &pins[pin];
	if (!pindesc->timer)
		return;

	if (value >= pindesc->timer->ARR)
	{
		digitalWrite(pin, 1);
		return;
	}
	else if (value == 0)
	{
		digitalWrite(pin, 0);
		return;
	}

	uint8_t mode = getPinMode(pin);
	if (mode == OPENDRAIN)
		pinMode(pin, OPENDRAIN_ALT);
	else
		pinMode(pin, OUTPUT_ALT);


	TIM_OCInitTypeDef TIM_OCStruct =
	{
			.TIM_OCMode = TIM_OCMode_PWM1,
			.TIM_OutputState = TIM_OutputState_Enable,
			.TIM_OutputNState = TIM_OutputNState_Disable,
			.TIM_Pulse = value,
			.TIM_OCPolarity = TIM_OCPolarity_High,
			.TIM_OCNPolarity = TIM_OCNPolarity_High,
			.TIM_OCIdleState = TIM_OCIdleState_Reset,
			.TIM_OCNIdleState = TIM_OCNIdleState_Reset
	};

	switch (pindesc->pwmchannel)
	{
	case TIM_Channel_1:
		TIM_OC1Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC1PreloadConfig(pindesc->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC2PreloadConfig(pindesc->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC3PreloadConfig(pindesc->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC4PreloadConfig(pindesc->timer, TIM_OCPreload_Enable);
		break;
	}
}

void stopPWM(uint8_t pin)
{
	if (pin >= PIN_COUNT)
		return;
	const pindesc_t *pindesc = &pins[pin];
	if (!pindesc->timer)
		return;

	uint8_t mode = getPinMode(pin);
	if (mode == OPENDRAIN_ALT)
		pinMode(pin, OPENDRAIN);
	else if (mode == OUTPUT_ALT)
		pinMode(pin, OUTPUT);

	TIM_OCInitTypeDef TIM_OCStruct =
	{
			.TIM_OCMode = TIM_OCMode_PWM1,
			.TIM_OutputState = TIM_OutputState_Disable,
			.TIM_OutputNState = TIM_OutputNState_Disable,
			.TIM_Pulse = 0,
			.TIM_OCPolarity = TIM_OCPolarity_High,
			.TIM_OCNPolarity = TIM_OCNPolarity_High,
			.TIM_OCIdleState = TIM_OCIdleState_Reset,
			.TIM_OCNIdleState = TIM_OCNIdleState_Reset
	};

	switch (pindesc->pwmchannel)
	{
	case TIM_Channel_1:
		TIM_OC1Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC1PreloadConfig(pindesc->timer, TIM_OCPreload_Disable);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC2PreloadConfig(pindesc->timer, TIM_OCPreload_Disable);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC3PreloadConfig(pindesc->timer, TIM_OCPreload_Disable);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(pindesc->timer, &TIM_OCStruct);
		TIM_OC4PreloadConfig(pindesc->timer, TIM_OCPreload_Disable);
		break;
	}
}
