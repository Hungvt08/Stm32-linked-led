#include <stdio.h>
#include <stdint.h>
#include "main.h"

#define GPIOD_ADDR 0x40020C00

void led_init()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	uint32_t* GPIOD_MODER = (uint32_t*)(GPIOD_ADDR + 0x00);
	*GPIOD_MODER &= ~(0b11 << 24);
	*GPIOD_MODER &= ~(0b11 << 26);
	*GPIOD_MODER &= ~(0b11 << 28);
	*GPIOD_MODER &= ~(0b11 << 30);
	*GPIOD_MODER |= (0b01 << 24)|(0b01 << 26)|(0b01 << 28)|(0b01 << 30);
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
	uint32_t* GPIOD_ODR = (uint32_t*)(GPIOD_ADDR + 0x14);
	if(Led_state == 1)
	{
		*GPIOD_ODR |= (1 << led_num);
	}
	else
	{
		*GPIOD_ODR &= ~(1 << led_num);
	}
}
int main()
{
	HAL_Init();
	led_init();
	while(1)
	{
		led_ctrl(LED_BLUE, 1);
		HAL_Delay(1000);
		led_ctrl(LED_BLUE, 0);
		HAL_Delay(1000);
		led_ctrl(LED_GREEN, 1);
		HAL_Delay(1000);
		led_ctrl(LED_GREEN, 0);
		HAL_Delay(1000);
		led_ctrl(LED_ORANGE, 1);
		HAL_Delay(1000);
		led_ctrl(LED_ORANGE, 0);
		HAL_Delay(1000);
		led_ctrl(LED_RED, 1);
		HAL_Delay(1000);
		led_ctrl(LED_RED, 0);
		HAL_Delay(1000);
	}
	return 0;
}
