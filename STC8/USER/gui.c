#include "gui.h"
#include "oled.h"

int ChsPos = 0;

void GuiInit(){
    //OLED初始化
    OLED_Init();
    OLED_Display_On();
    //清屏
    OLED_Clear();
    //三通道标识
    OLED_ShowChar(25,2,'R',15);
    OLED_ShowChar(65,2,'G',15);
    OLED_ShowChar(105,2,'B',15);
    //三通道值
    OLED_ShowNum(10,4,1,4,15);
    OLED_ShowNum(50,4,1,4,15);
    OLED_ShowNum(90,4,1,4,15);
    //通道选择标识
    OLED_ShowChar(25,5,'^',15);
}

//光标左移
void ChsShiftL(){
    switch (ChsPos)
    {
    case 1:
        OLED_ShowChar(65,5,' ',15);
        OLED_ShowChar(25,5,'^',15);
        ChsPos--;
        break;
    case 2:
        OLED_ShowChar(105,5,' ',15);
        OLED_ShowChar(65,5,'^',15);
        ChsPos--;
        break;
    default:
        break;
    }
}

//光标右移
void ChsShiftR(){
    switch (ChsPos)
    {
    case 0:
        OLED_ShowChar(25,5,' ',15);
        OLED_ShowChar(65,5,'^',15);
        ChsPos++;
        break;
    case 1:
        OLED_ShowChar(65,5,' ',15);
        OLED_ShowChar(105,5,'^',15);
        ChsPos++;
        break;
    default:
        break;
    }
}

//改变通道值
void ChangeChsValue(int index, int value){
    switch (index)
    {
    case 0://R
        OLED_ShowNum(10,4,value,4,15);
        break;

    case 1://G
        OLED_ShowNum(50,4,value,4,15);
        break;

    case 2://B
        OLED_ShowNum(90,4,value,4,15);
        break;

    default:
        break;
    }
}

int GetChsPos(){
    return ChsPos;
}