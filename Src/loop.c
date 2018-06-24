#include "stm32f1xx_hal.h"
#include "def.h"


//  var  ----
int c=0, r=0;
int v[4]={2,1, 3,5};


//  Loop  ----
void Loop()
{
	int i,d, rr;
	//  set coumns
	rr = r-1;
	if (rr>=0 && rr<7)
	for (d=0; d<4; ++d)
	{
		uint u = Digits[v[d]][rr];
		for (i=0; i<5; ++i)
			Set(Port[d][i], Pin[d][i], u & (1<<(4-i)));
	}
	HAL_Delay(10);

	for (d=0; d<4; ++d)
	for (i=0; i<5; ++i)
		Set(Port[d][i], Pin[d][i], 0);
	HAL_Delay(1);

	++c;  // clock
	//if (c % 100 == 1)
	{
		if (r == 0 || r == 1)
		{
			Set(2, 13, r == 0 ? 0 : 1);  // data
			HAL_Delay(1);
		}

		Set(2, 14, 0);
		HAL_Delay(1);
		Set(2, 14, 1);  // clk
		HAL_Delay(1);

		++r;
		if (r > 8)
			r = 0;
	}

	//  inc
	if (c % 100 == 0)
	{
		++v[3];  if (v[3]>9) {  v[3]=0;
		++v[2];  if (v[2]>9) {  v[2]=0;
		++v[1];  if (v[1]>9) {  v[1]=0;
		++v[0];  if (v[0]>9) {  v[0]=0;  }
		}	}	}
	}
}
