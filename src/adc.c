/*
 * adc.c
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#include <system.h>
#include <stm32f10x_adc.h>

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStruct =
	{
			.ADC_Mode = ADC_Mode_Independent,
			.ADC_ScanConvMode = DISABLE,
			.ADC_ContinuousConvMode = DISABLE,
			.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None,
			.ADC_DataAlign = ADC_DataAlign_Left,
			.ADC_NbrOfChannel = 1
	};
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	wait(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	wait(ADC_GetCalibrationStatus(ADC1));

	ADC_Init(ADC2, &ADC_InitStruct);
	ADC_Cmd(ADC2, ENABLE);

	ADC_ResetCalibration(ADC2);
	wait(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	wait(ADC_GetCalibrationStatus(ADC2));

	ADC_TempSensorVrefintCmd(ENABLE);
}

uint8_t ADC_Resolution = 10;

uint16_t analogRead(uint8_t pin)
{
	if (pin < A0)
		pin += A0;

	ADC_TypeDef *ADC = NULL;
	uint8_t channel = 0;

	if (pin < PIN_COUNT) // We are talking about an ADC pin
	{
		pinMode(pin, ANALOG);
		const pindesc_t *pindesc = &pins[pin];
		if (!pindesc->adc)
			return 0;

		ADC = pindesc->adc;
		channel = pindesc->adchannel;
	}
	else if (pin == VREF) // We are measuring internal VREF
	{
		ADC = ADC1;
		channel = ADC_Channel_Vrefint;
	}
	else if (pin == TEMP) // We are measuring chip teperature
	{
		ADC = ADC1;
		channel = ADC_Channel_TempSensor;
	}

	if (!ADC)
		return 0;

	ADC_ClearFlag(ADC, ADC_FLAG_EOC);
	ADC_RegularChannelConfig(ADC, channel, 1, ADC_SampleTime_13Cycles5);
	ADC_Cmd(ADC, ENABLE);
	wait(ADC_GetFlagStatus(ADC, ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC) >> (16 - ADC_Resolution);
}

void analogReadResolution(uint8_t bits)
{
	ADC_Resolution = bits;
}
