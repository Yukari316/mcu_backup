#ifndef __GUI_H
#define __GUI_H 

#include "STC8.H"

void GuiInit();
void ChsShiftL();
void ChsShiftR();
void ChangeChsValue(int index, int value);
int GetChsPos();

#endif