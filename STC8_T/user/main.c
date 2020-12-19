#include "STC8F.H"
#include "main.h"
#include "stdio.h"
#include "sys\uart.h"
#include "sys\ADC.h"
#include "sensor\LMT70.h"
#include "sys\gpio.h"

extern int AdcFlag;

unsigned int ADC = 0;
unsigned char UartRx = 0;

float ADCV = 0;
char ADCChannelIndex = 0;
float Temp = 0;
char TempStr[10];
char ToSendStr[5];
int ReturnValueTemp[3];
int ReturnValueVoltage[3];
int i;

void main()
{
	//初始化
	GpioInit();
	UartInit();
	AdcInit();
	
	while(1){
		if(!P24){//ASCII模式
			for(i = 0;i < 3;i++){
				sprintf(TempStr,"A%d = %f",i,(float)ReturnValueTemp[i]/10 - 55);
				SendStr(TempStr,10);
				SendStr(" ",1);
			}
			SendStr("\r\n",2);
		}else{//16进制模式
			if(!P22 && RI){//查询发送
				switch(SBUF){
					//发送单独通道
					case 0xA0:case 0xA1:case 0xA2:
						Send_Byte(SBUF);
						if(P23){//发送温度
							Send_Byte(ReturnValueTemp[SBUF - 0xA0]>>8);
							Send_Byte(ReturnValueTemp[SBUF - 0xA0]);
						}else{//发送电压
							Send_Byte(ReturnValueVoltage[SBUF - 0xA0]>>8);
							Send_Byte(ReturnValueVoltage[SBUF - 0xA0]);
						}
						break;
					case 0xA3:
						//发送所有通道
						for(i = 0;i < 3;i++){
							Send_Byte(0xA0+i);
							//判断端口
							if(P23){//发送温度
								Send_Byte(ReturnValueTemp[i]>>8);
								Send_Byte(ReturnValueTemp[i]);
							}else{//发送电压
								Send_Byte(ReturnValueVoltage[i]>>8);
								Send_Byte(ReturnValueVoltage[i]);
							}
						}
						break;
				}
				RI = 0;
			}else{//连续发送
				for(i = 0;i < 3;i++){
					Send_Byte(0xA0+i);
					//判断端口
					if(P23){//发送温度
						Send_Byte(ReturnValueTemp[i]>>8);
						Send_Byte(ReturnValueTemp[i]);
					}else{//发送电压
						Send_Byte(ReturnValueVoltage[i]>>8);
						Send_Byte(ReturnValueVoltage[i]);
					}
				}
			}
		}
		//ADC转换
		if(AdcFlag){
			AdcFlag = 0;
			//读ADC值
			ADC = ADC_RES * 256 + ADC_RESL;
			//计算ADC电压
			ADCV = 2500 * (float)ADC / 4096;
	
			//发送编号
			switch(ADCChannelIndex){
				case 0:
					ADC_CONTR = 0x82;
					ADCChannelIndex++;
					break;
				case 1:
					ADC_CONTR = 0x83;
					ADCChannelIndex++;
					break;
				case 2:
					ADC_CONTR = 0x84;
					ADCChannelIndex = 0;
					break;
			}
			ReturnValueVoltage[ADCChannelIndex] = ADCV * 10;
			//得到温度
			Temp = QueryTemp(ADCV);
			ReturnValueTemp[ADCChannelIndex] = (Temp + 55) * 10;
			//启动ADC
			ADC_CONTR |= 0x40;
		}
	}
}