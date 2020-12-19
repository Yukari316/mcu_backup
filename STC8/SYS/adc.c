#include "adc.h"
#include "gui.h"
#include "button.h"

int ADCValue = 0;

void ADCInit(){
    P0M0 = 0x00;                                //设置P0.0为ADC口
    P0M1 = 0x01;
    ADCCFG = 0x2F;                              //设置ADC时钟为系统时钟/2/16/16
    ADC_CONTR = 0x88;                           //使能ADC模块
    EA = 1;
    EADC = 1;                                   //使能ADC中断
    ADC_CONTR |= 0x40;                          //启动AD转换
}

void ADC_Isr() interrupt 5
{
    ADC_CONTR &= ~0x20;                         //清中断标志
    //读取ADC结果
    ADCValue = ADC_RESL;
    ADCValue += ADC_RES << 8;

    GetBottonAdcValue(ADCValue);

    ADC_CONTR |= 0x40;                          //继续AD转换
}