#include "uart.h"
#include "stdio.h"


//串口常用函数
void UartInit()		//9600bps@24.000MHz
{
	SCON = 0x40;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x8F;		//设定定时初值
	TH1 = 0xFD;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	REN=1;		//接受使能

	
	//启用串口中断
	//EA=1;
	//ES=1;
	
	TR1 = 1;		//启动定时器1
}

/*
void Uart() interrupt 4{//数据接收
	if(TI) TI=0;//发送中断
	if(RI) RI=0;//接收中断
}*/

void Send_Byte(unsigned char c)//发送字节数据
{
	SBUF = c;//设置缓冲寄存器
  while(!TI);//发送后自动置1	
  TI=0;
}

void SendStr(char *Data , char length)//数据发送函数
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		Send_Byte(Data[i]);
	}
}