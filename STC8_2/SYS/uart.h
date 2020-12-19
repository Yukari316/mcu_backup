#ifndef __UART_H_
#define __UART_H_

#include "STC8F.H"

void UartInit();
void Uart2Init();
void Send_Byte(unsigned char c);
void SendStr(char *Data , char length);
void Send_Byte2(unsigned char c);
void SendStr2(char *Data , char length);
void Delay500ms();

#endif