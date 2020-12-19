#include "gpio.h"

void GpioInit(){
	P2M0 = 0x00;
	P2M1 = 0x00;
	P22 = 1;
	P23 = 1;
	P24 = 1;
}