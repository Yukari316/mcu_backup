#include "uart.h"
#include "stdio.h"

char str[1];
unsigned int buffer;
bit busy_1 = 0;
int hun = 0;
int ten = 0;
int dig = 0;

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
	EA=1;
	ES=1;
	
	TR1 = 1;		//启动定时器1
}

void Uart2Init()		//9600bps@24.000MHz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x8F;		//设定定时初值
	T2H = 0xFD;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}


void Uart() interrupt 4{//数据接收
	if(TI) {//发送中断
		TI = 0;
		busy_1 = 0;
	}
	if(RI) {//接收中断
		RI = 0;
		buffer = SBUF;
		
		hun = buffer / 100;
		ten = buffer / 10 - 10 * hun;
		dig = buffer - hun * 100 - ten * 10;
		
		if(hun != 0){
			//百位
			sprintf(str,"A8:02/%d*WAV",hun);
			SendStr2(str,12);
			Delay500ms();
			SendStr2("A8:02/B*MP3",12);
			Delay500ms();
		}
		if(ten != 0){
			//十位
			if(buffer > 20){
				sprintf(str,"A8:02/%d*WAV",ten);
				SendStr2(str,12);
				Delay500ms();
			}
			SendStr2("A8:02/S*MP3",12);
			Delay500ms();
		}
		if(dig != 0){
			//个位
			sprintf(str,"A8:02/%d*WAV",dig);
			SendStr2(str,12);
		}
		if(buffer == 0){
			SendStr2("A8:02/0*WAV",12);
		}
	}
}

void Send_Byte(unsigned char c)//发送字节数据
{
	SBUF = c;//设置缓冲寄存器
	busy_1 = 1;
  while(busy_1);	
}

void SendStr(char *Data , char length)//数据发送函数
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
		Send_Byte(Data[i]);
	}
}

void Send_Byte2(unsigned char c)//发送字节数据
{
	S2BUF = c;//设置缓冲寄存器
  while(!(S2CON & 0x02));//发送后自动置1	 
	S2CON &= ~0x02;
}

void SendStr2(char *Data , char length)//数据发送函数
{
	unsigned char k;
	for(k=0;k<length;k++)
	{
		Send_Byte2(Data[k]);
	}
}

void Delay500ms()		//@24.000MHz
{
	unsigned char i, j, k;

	;
	;
	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
