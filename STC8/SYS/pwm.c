#include "pwm.h"
#include "gui.h"

int ValR = 0x001;
int ValG = 0x001;
int ValB = 0x001;

void PwmInit(){
    P_SW2 = 0x80;
    PWMCKS = 0x00;//PWM时钟
    PWMC = 0x100;
    //0通道 R
    PWM0T1 = 0x000;
    PWM0T2 = ValR;
    
    //1通道 G
    PWM1T1 = 0x000;
    PWM1T2 = ValG;

    //2通道 B
    PWM1T1 = 0x000;
    PWM1T2 = ValB;

    PWM0CR = 0x80;
    PWM1CR = 0x80;
    PWM2CR = 0x80;

    P_SW2 = 0x00;

    PWMCR = 0xC0;

    EA = 1;
}

//通道值增加
void ChsValueAdd(int index){
    switch (index){
    case 0:
        if(ValR < 255){
            ValR++;
            ChangeChsValue(0,ValR);
        }
        break;

    case 1:
        if(ValG < 255){
            ValG++;
            ChangeChsValue(1,ValG);
        }
        break;

    case 2:
        if(ValB < 255){
            ValB++;
            ChangeChsValue(2,ValB);
        }
        break;
    
    default:
        break;
    }
}

//通道值减少
void ChsValueSub(int index){
    switch (index){
        case 0:
            if(ValR > 1){
                ValR--;
                ChangeChsValue(0,ValR);
            }
            break;

        case 1:
            if(ValG > 1){
                ValG--;
                ChangeChsValue(1,ValG);
            }
            break;

        case 2:
            if(ValB > 1){
                ValB--;
                ChangeChsValue(2,ValB);
            }
            break;
        
        default:
            break;
    }
}

void PWM_Isr() interrupt 22{
    PWMCFG &= ~0x80;
    P_SW2 |= 0x80;
    PWM0T2 = ValR;
    PWM1T2 = ValG;
    PWM2T2 = ValB;
    P_SW2 &= ~0x80;
}