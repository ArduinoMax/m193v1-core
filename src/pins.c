/*
 * pins.c
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#include <pins_arduino.h>
#include <stddef.h>

/* Pin map:
 *
 * Pin		Digital	Analog	Alt		Alt2	PWM		ADC
 *
 * PA0		D15		WAKEUP
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

#ifndef TIM_Channel_0
#define TIM_Channel_0	0
#endif

void AFIO_Configuration(void)
{
	GPIO_AFIODeInit();
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
}

const pindesc_t pins[] =
		{
				{ 0, 10,	NULL, ADC_Channel_0,	TIM1, TIM_Channel_3 }, // D0
				{ 0, 9,		NULL, ADC_Channel_0,	TIM1, TIM_Channel_2 },
				{ 1, 12,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 13,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 14,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 15,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 0, 8,		NULL, ADC_Channel_0,	TIM1, TIM_Channel_1 },
				{ 1, 4,		NULL, ADC_Channel_0,	TIM3, TIM_Channel_1 },

				{ 1, 5,		NULL, ADC_Channel_0,	TIM3, TIM_Channel_2 }, // D8
				{ 1, 6,		NULL, ADC_Channel_0,	TIM4, TIM_Channel_1 },
				{ 1, 7,		NULL, ADC_Channel_0,	TIM4, TIM_Channel_2 },
				{ 1, 11,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 10,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 2,		NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },

				{ 2, 13,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 }, // D14
				{ 0, 0,		NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 8,		NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },
				{ 1, 9,		NULL, ADC_Channel_0,	NULL, TIM_Channel_0 },

				{ 0, 2,		ADC1, ADC_Channel_2,	TIM2, TIM_Channel_3 }, // A0
				{ 0, 1,		ADC1, ADC_Channel_1,	TIM2, TIM_Channel_2 },
				{ 0, 3,		ADC1, ADC_Channel_3,	TIM2, TIM_Channel_4 },
				{ 0, 4,		ADC1, ADC_Channel_4,	NULL, TIM_Channel_0 },
				{ 1, 0,		ADC1, ADC_Channel_8,	TIM3, TIM_Channel_3 },
				{ 1, 1,		ADC1, ADC_Channel_9,	TIM3, TIM_Channel_4 },

				{ 0, 5,		ADC2, ADC_Channel_5,	NULL, TIM_Channel_0 }, // SPI
				{ 0, 6,		ADC2, ADC_Channel_6,	NULL, TIM_Channel_0 },
				{ 0, 7,		ADC2, ADC_Channel_7,	NULL, TIM_Channel_0 },

				{ 0, 11,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 }, // USB
				{ 0, 12,	NULL, ADC_Channel_0,	NULL, TIM_Channel_0 }
		};
