#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define GPIOD_BASE_ADDR 0x40020C00
#define GPIOA_BASE_ADDR 0x40020000
void led_init()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 24);
	*GPIOD_MODER &= ~(0b11 << 26);
	*GPIOD_MODER &= ~(0b11 << 28);
	*GPIOD_MODER &= ~(0b11 << 30);
	*GPIOD_MODER |= (0b01 << 24)|(0b01 << 26)|(0b01 << 28)|(0b01 << 30);
}
void button_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	uint32_t* gpioa_moder = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*gpioa_moder &= ~(0b11 << 0);
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
void button_handle()
{
	if(button_get_state() == 1)
	{
		led_ctrl(LED_RED,1);
	}
	else
	{
		led_ctrl(LED_RED, 0);
	}
}
int main()
{
	HAL_Init();
	led_init();
	button_init();
	while(1)
	{
		led_ctrl(LED_BLUE, 1);
		HAL_Delay(1000);
		led_ctrl(LED_BLUE, 0);
		HAL_Delay(1000);
		button_handle();
	}
	return 0;
}
