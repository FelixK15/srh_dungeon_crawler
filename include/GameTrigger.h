#ifndef __GAMETRIGGER__
#define __GAMETRIGGER__

#include "GameTypes.h"

Trigger *CreateTrigger(int iPosX,int iPosY,int iWidth,int iHeight,TriggerHandler pHandler);

void ExitTrigger();
void GuardTrigger();

#endif