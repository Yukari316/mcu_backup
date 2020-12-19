#include "pwm.h"
#include "adc.h"
#include "gui.h"

void main()
{
    PwmInit();
    GuiInit();
    ADCInit();

    while (1)
    {
    }
}