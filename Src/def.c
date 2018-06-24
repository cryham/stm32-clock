#include "stm32f1xx_hal.h"

GPIO_TypeDef* Ports[4] = {GPIOA, GPIOB, GPIOC, GPIOD};

//  LEDs  yellow,green  port,pin
const uint
	YlwPo = 1, YlwPi = 14,
	GrnPo = 1, GrnPi = 13;
