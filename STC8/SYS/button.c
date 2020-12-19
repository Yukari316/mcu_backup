#include "button.h"
#include "gui.h"
#include "oled.h"
#include "adc.h"
#include "pwm.h"
#include <intrins.h>

int ChangeFlag = 0;
int GetFristADC = 0;
int FirstADCTFlag = 0;

void GetBottonAdcValue(int adcValue){
    if(FirstADCTFlag){
        if(adcValue > 3953) ChangeFlag = 0;
        if(adcValue <= 3953 && adcValue > 3684 && !ChangeFlag){//UP
            ChsValueAdd(GetChsPos());
            OLED_ShowString(1,7,"UP  ",15);
            OLED_ShowNum(35,7,ADCValue,4,15);
        }
        if(adcValue <= 3684 && adcValue > 3379 && !ChangeFlag){//LEFT
            ChsShiftL();
            OLED_ShowString(1,7,"L   ",15);
            OLED_ShowNum(35,7,ADCValue,4,15);
            ChangeFlag = 1;
        }
        if(adcValue <= 3379 && adcValue > 2941 && !ChangeFlag){//RIGHT
            ChsShiftR();
            OLED_ShowString(1,7,"R   ",15);
            OLED_ShowNum(35,7,ADCValue,4,15);
            ChangeFlag = 1;
        }
        if(adcValue <= 2237 && adcValue > 0 && !ChangeFlag){//DOWN
            ChsValueSub(GetChsPos());
            OLED_ShowString(1,7,"DOWN",15);
            OLED_ShowNum(35,7,ADCValue,4,15);
        }
        FirstADCTFlag = 0;
    }else
    {
        Delay50ms();
        GetFristADC = adcValue;
        FirstADCTFlag = 1;
    }
}

void Delay50ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 7;
	j = 23;
	k = 105;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

