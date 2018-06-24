#include "stm32f1xx_hal.h"
#include "def.h"


//  var  ----
extern RTC_HandleTypeDef hrtc;

char key[4]={0,};  // state
char ylw = 0, grn = 0, inc = 0;

int c=0, r=0;
int v[4]={2,1, 3,5};


//  Loop  ----
void Loop()
{
	//  set column bits in 1 row
	int i,d, rr = r-1;

	if (rr>=0 && rr<7)
	for (d=0; d<4; ++d)
	{
		//  empty 1st zero
		if (d==0 && v[d]==0)
		{	for (i=0; i<5; ++i)
				Set(Port[d][i], Pin[d][i], 0);
		}else{
			uint u = Digits[v[d]][rr];
			for (i=0; i<5; ++i)
				Set(Port[d][i], Pin[d][i], u & (1<<(4-i)));
		}
	}
	HAL_Delay(10);

	for (d=0; d<4; ++d)
	for (i=0; i<5; ++i)
		Set(Port[d][i], Pin[d][i], 0);
	HAL_Delay(1);


	//  rows, shifter
	if (r == 0 || r == 1)
	{
		Set(RowDPo, RowDPi, r == 0 ? 0 : 1);  // data
		HAL_Delay(1);
	}

	Set(RowClkPo, RowClkPi, 0);  // clk
	HAL_Delay(1);
	Set(RowClkPo, RowClkPi, 1);
	HAL_Delay(1);

	++r;
	if (r > 8)
		r = 0;
	++c;


	//  read keys
	for (i=0; i<4; ++i)
		key[i] = Get(KPort[i], KPin[i]) ? 1 : 0;

	if (key[0] && c%150==0)  {  ylw = 1-ylw;  Set(YlwPo, YlwPi, ylw);  }
	if (key[3] && c%150==0)  {  grn = 1-grn;  Set(GrnPo, GrnPi, grn);  }


	//  rtc time
	RTC_TimeTypeDef sTime;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK)
	{
		//sTime.Hours
		v[0] = sTime.Minutes / 10;
		v[1] = sTime.Minutes % 10;
		v[2] = sTime.Seconds / 10;
		v[3] = sTime.Seconds % 10;
	}

	//if (HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BCD) != HAL_OK)
	//{  sDate.Date, sDate.Month, sDate.Year);  }
}
