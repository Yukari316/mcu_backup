#ifndef __ADC_H_
#define __ADC_H_

#include "STC8F.H"

void AdcInit();
void AdcStart();
void SwitchChs(int chs);

#endif