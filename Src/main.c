#include "stm32f1xx_hal.h"
#include "def.h"


void GPIO_Init();
extern void Loop();


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
//  in case of error
void _Error_Handler(char *file, int line)
{
	while(1) {	}
}

//  RCC Osc and Clock config
void RCC_Config(void)
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
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//  Configure GPIO pin output level
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;

	//  leds
	Init(YlwPo, YlwPi);
	Init(GrnPo, GrnPi);
}
