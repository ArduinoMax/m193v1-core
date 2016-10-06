/*
 * rcc.c
 *
 *  Created on: 2016Äê10ÔÂ6ÈÕ
 *      Author: max
 */

#include <system.h>
#include <stm32f10x_rcc.h>

void RCC_Configuration(void)
{
	// Reset RCC.
	RCC_DeInit();

	// We are now running on internal 8MHz clock. If the external crystal have
	// one of the supported frequencies, it will start the PLL on it and switch
	// over to 72MHz operation when supported, or 48MHz if not.

#if		HSE_VALUE ==	 3000000 \
	 || HSE_VALUE ==	 4000000 \
	 || HSE_VALUE ==	 6000000 \
	 || HSE_VALUE ==	 8000000 \
	 || HSE_VALUE ==	12000000 \
	 || HSE_VALUE ==	16000000 \
	// Those are the supported crystal frequencies.
#define USE_HSE
#endif

#ifdef USE_HSE
	RCC_HSEConfig(RCC_HSE_ON);
	wait(RCC_WaitForHSEStartUp() != SUCCESS);
#endif

#if		HSE_VALUE ==	 3000000	// 3MHz
	// F_PLL = HSE_VALUE * 16			= 48MHz
#define PLL_48
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_16);
#elif	HSE_VALUE ==	 4000000	// 4MHz
	// F_PLL = HSE_VALUE * 12			= 48MHz
#define PLL_48
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_12);
#elif	HSE_VALUE ==	 6000000	// 6MHz
	// F_PLL = HSE_VALUE * 12			= 72MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_12);
#elif	HSE_VALUE ==	 8000000	// 8MHz
	// F_PLL = HSE_VALUE * 9			= 72MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
#elif	HSE_VALUE ==	12000000	// 12MHz
	// F_PLL = HSE_VALUE * 6			= 72MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
#elif HSE_VALUE ==	16000000	// 16MHz
	// F_PLL = HSE_VALUE / 2 * 9	= 72MHz
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
#else													// Unsupported clock frequency
	// F_PLL = HSI_VALUE / 2 * 12	= 48MHz
#define PLL_48
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
#endif

	// Start PLL
	RCC_PLLCmd(ENABLE);

	// F_AHB = F_PLL
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	// F_APB2 = F_PLL
	RCC_PCLK2Config(RCC_HCLK_Div1);

	// The following settings differ due to PLL frequency.
#ifdef PLL_48
	// F_APB1 = F_PLL
	RCC_PCLK1Config(RCC_HCLK_Div1);

	// FLASH need to be slowed downbased on PLL frequency.
	FLASH_SetLatency(FLASH_Latency_1);
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	// F_ADC = F_PLL / 4
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);

	// F_USB = F_PLL
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
#else
	// F_APB1 = F_PLL / 2
	RCC_PCLK1Config(RCC_HCLK_Div2);

	// FLASH need to be slowed downbased on PLL frequency.
	FLASH_SetLatency(FLASH_Latency_2);
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	// F_ADC = F_PLL / 6
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	// F_USB = F_PLL / 1.5
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
#endif

	// Shift gears when clock is ready.
	wait(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	wait(RCC_GetSYSCLKSource() != 0x08);

	// Enable peripherals
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2 |
		RCC_AHBPeriph_CRC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA |
		RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
		RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 |
		RCC_APB1Periph_TIM4 | RCC_APB1Periph_WWDG | RCC_APB1Periph_USB |
		RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);

	// Enable LSE clock
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_ON);

	// Enable RTC on LSE clock
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
}
