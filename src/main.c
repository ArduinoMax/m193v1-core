
#include <system.h>
#include <stm32f10x.h>

int main(void)
{
	RCC_Configuration();
	SysTick_Configuration();
	GPIO_Configuration();
	AFIO_Configuration();
	EXTI_Configuration();
	TIM_Configuration();
	ADC_Configuration();

	setup();

	for (;;)
	{
		yield();
		loop();
	}
}

void __attribute__((weak)) setup(void) {}
void __attribute__((weak)) loop(void) {}
