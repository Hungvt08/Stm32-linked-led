#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define GPIOD_BASE_ADDR 0x40020C00
#define GPIOA_BASE_ADDR 0x40020000
#define EXTI0_BASE_ADDR 0x40013C00
void led_init()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 24);
	*GPIOD_MODER &= ~(0b11 << 26);
	*GPIOD_MODER &= ~(0b11 << 28);
	*GPIOD_MODER &= ~(0b11 << 30);
	*GPIOD_MODER |= (0b01 << 24)|(0b01 << 26)|(0b01 << 28)|(0b01 << 30);
	// mode open-drain
	uint32_t *GPIOD_OTYPER = (uint32_t*)(GPIOD_BASE_ADDR + 0x04);
	*GPIOD_OTYPER &= ~((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));
}
void button_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* gpioa_moder = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*gpioa_moder &= ~(0b11 << 0);
	//mode pull up
	uint32_t* GPIOA_PUPDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x0C);
	*GPIOA_PUPDR &= ~(0b11 << 0);
	*GPIOA_PUPDR |=  (0b10 << 0);
}
int button_get_state()
{
	uint32_t* GPIOA_IDR = (uint32_t*)(GPIOA_BASE_ADDR + 0x10);
	if(((*GPIOA_IDR >> 0) &1) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
enum
{
	LED_GREEN = 12,
	LED_ORANGE,
	LED_RED,
	LED_BLUE
};
void led_ctrl(int led_num,int Led_state)
{
	uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_BASE_ADDR + 0x14);
	if(Led_state == 1)
	{
		*GPIOD_ODR |= (1 << led_num);
	}
	else
	{
		*GPIOD_ODR &= ~(1 << led_num);
	}
}
void EXTI_interrupt_init()
{
	uint32_t* EXTI0_FTSR = (uint32_t*)(EXTI0_BASE_ADDR + 0x0C);
	*EXTI0_FTSR |= (1 << 0);
	uint32_t* EXTI0_RTSR = (uint32_t*)(EXTI0_BASE_ADDR + 0x08);
	*EXTI0_RTSR |= (1 << 0);
	uint32_t* EXTI0_IMR = (uint32_t*)(EXTI0_BASE_ADDR + 0x00);
	*EXTI0_IMR |= (1 << 0);
	// config NVIC
	uint32_t* NVIC_ISER0 = (uint32_t*) (0xE000E100 + 0x00);
	*NVIC_ISER0 |= (1 << 6);
}
void EXTI0_IRQHandler()
{
	static int old_button_led = 0;
	static int led_state = 0;
	int current_button_led;
	current_button_led = button_get_state();
	if(old_button_led == 1 && current_button_led == 0)
	{
			led_state = !led_state;
			led_ctrl(LED_RED, led_state);
	}
	old_button_led = current_button_led;
//	if(button_get_state() == 1)
//	{
//		led_ctrl(LED_RED, 1);
//	}
//	else
//	{
//		led_ctrl(LED_RED, 0);
//	}
	uint32_t* EXTI_PR = (uint32_t*)(EXTI0_BASE_ADDR + 0x14);
	*EXTI_PR |= (1 << 0);
}
int main()
{
	HAL_Init();
	led_init();
	button_init();
	EXTI_interrupt_init();
	while(1)
	{
		led_ctrl(LED_BLUE, 1);
		HAL_Delay(1000);
		led_ctrl(LED_BLUE, 0);
		HAL_Delay(1000);
	}
	return 0;
}
