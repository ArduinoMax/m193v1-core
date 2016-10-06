/*
 * system.h
 *
 *  Created on: 2016Äê9ÔÂ30ÈÕ
 *      Author: max
 */

#ifndef INCLUDE_SYSTEM_H_
#define INCLUDE_SYSTEM_H_

#include <Arduino.h>
#include <tools.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

void RCC_Configuration(void);
void GPIO_Configuration(void);
void AFIO_Configuration(void);
void EXTI_Configuration(void);
void SysTick_Configuration(void);
void TIM_Configuration(void);
void ADC_Configuration(void);

__END_DECLS

#endif /* INCLUDE_SYSTEM_H_ */
