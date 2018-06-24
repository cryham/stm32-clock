#include "stm32f1xx_hal.h"
#include "def.h"


void GPIO_Init();
void RCC_Config();
extern void Loop();


//  application entry point
//
int main()
{
	//  Reset, SysTick at 1ms
	HAL_Init();

	RCC_Config();

	//  Initialize peripherals
	GPIO_Init();

	while (1)
	{
		Loop();
	}
}


//  GPIO util
//  in case of error
void _Error_Handler(char *file, int line)
{
	while(1) {	}
}

//  RCC Osc and Clock config
void RCC_Config()
{
	RCC_OscInitTypeDef osc;
	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState = RCC_HSE_ON;
	osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	osc.HSIState = RCC_HSI_ON;
	osc.PLL.PLLState = RCC_PLL_ON;
	osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&osc) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

	RCC_ClkInitTypeDef clk;
	clk.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
				  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk.APB1CLKDivider = RCC_HCLK_DIV2;
	clk.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2) != HAL_OK)
		_Error_Handler(__FILE__, __LINE__);

	//  Configure Systick interrupt time
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 10000);  // param
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


//  Configure pins  ----
void GPIO_Init()
{
	GPIO_InitTypeDef gpio;

	//  GPIO ports clock enable
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//  Configure GPIO pin output level
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;

	//  Configure GPIO pins
	//  4 digits x 5 columns
	int d,i;
	for (d=0; d<4; ++d)
	for (i=0; i<5; ++i)
		Init(Port[d][i], Pin[d][i]);

	//  rows shifter, 4094
	Init(2, 13);
	Init(2, 14);

	//  LEDs
	Init(YlwPo, YlwPi);
	Init(GrnPo, GrnPi);
}
