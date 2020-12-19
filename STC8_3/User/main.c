#include "main.h"
#include "sys/uart.h"

void main(){
	UartInit();
	P2 = 0x00;
	
	while(1){
		P2 = 0x01;
		Delay3ms();
		P2 = 0x02;
		Delay3ms();
		P2 = 0x04;
		Delay3ms();
		P2 = 0x08;
		Delay3ms();
	}
}