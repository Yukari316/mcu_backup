#include "ADC.h"
#include "uart.h"

int AdcFlag = 0;

void AdcInit(){
	//设置P0.0/P0.1/P0.2口
	P1M0 = 0x00;
	P1M1 = 0x1C;
	
	ADCCFG = 0x2F;
	ADC_CONTR = 0x82;
	EADC = 1;
	EA = 1;
	
	//启动ADC
	ADC_CONTR |= 0x40;
}

void ADC_Isr() interrupt 5{
	AdcFlag=1;
	ADC_CONTR &= ~0x20;
}