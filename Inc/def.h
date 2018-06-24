#pragma once
#include "stm32f1xx_hal.h"


//  GPIO util
extern GPIO_TypeDef* Ports[4];

#define Init(port, pin) \
	{  gpio.Pin = 1u << (pin);  HAL_GPIO_Init(Ports[port], &gpio);  }

#define Set(port, pin, val) \
	HAL_GPIO_WritePin(Ports[port], 1u << (pin), (val) ? GPIO_PIN_SET : GPIO_PIN_RESET);

#define Get(port, pin) \
	(HAL_GPIO_ReadPin(ports[port], 1u << (pin)) == GPIO_PIN_RESET)


//  PINS config  ----

//  LEDs  yellow,green  port,pin
extern const uint
	YlwPo, YlwPi, GrnPo, GrnPi,

//  dot matrix  digit, column
	Port[4][5], Pin[4][5];


//  Digits font  value, row, column bits
extern const char Digits[10][7];
