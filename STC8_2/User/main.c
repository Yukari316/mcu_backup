#include "STC8F.H"
#include "main.h"
#include "stdio.h"
#include "SYS/uart.h"

void main()
{
	//���ڳ�ʼ��
	UartInit();
	Uart2Init();
	
	SendStr2("AF:30",6);
	while(1){
	}
}