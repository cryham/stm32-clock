#include "stm32f1xx_hal.h"


void GPIO_Init();

void Loop();


//  application entry point
//
int main()
{
	//  Reset, SysTick at 1ms
	HAL_Init();

	//  Initialize peripherals
	GPIO_Init();

	while (1)
	{
		Loop();
	}
}


//  GPIO util
GPIO_TypeDef* Ports[4] = {GPIOA, GPIOB, GPIOC, GPIOD};
#define Init(port, pin)       {  gpio.Pin = 1u << pin;  HAL_GPIO_Init(Ports[port], &gpio);  }
#define Set(port, pin, val)   HAL_GPIO_WritePin(Ports[port], 1u << pin, val ? GPIO_PIN_SET : GPIO_PIN_RESET);

//  LEDs
const char YlwPo = 1, YlwPi = 14;
const char GrnPo = 1, GrnPi = 13;


//  Configure pins  ----
void GPIO_Init()
{
	GPIO_InitTypeDef gpio;

	//  GPIO ports clock enable
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//  Configure GPIO pin output level
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;

	//  leds
	Init(YlwPo, YlwPi);
	Init(GrnPo, GrnPi);
}


//  Loop  ----
void Loop()
{
	Set(GrnPo, GrnPi, 0);
	HAL_Delay(20);
	Set(GrnPo, GrnPi, 1);
	HAL_Delay(20);
	Set(YlwPo, YlwPi, 1);
	//HAL_Delay(200);
}
