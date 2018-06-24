#include "stm32f1xx_hal.h"
#include "def.h"


//  Loop  ----
void Loop()
{
	Set(GrnPo, GrnPi, 0);
	HAL_Delay(10);
	Set(GrnPo, GrnPi, 1);
	HAL_Delay(10);
	Set(YlwPo, YlwPi, 1);
	//HAL_Delay(200);
}
