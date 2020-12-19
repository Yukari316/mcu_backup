#ifndef __UART_H_
#define __UART_H_

#include "STC8F.H"

void UartInit();
void Send_Byte(unsigned char c);
void SendStr(char *Data , char length);
void Delay3ms();

#endif