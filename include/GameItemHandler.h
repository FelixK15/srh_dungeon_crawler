#ifndef __GAMEITEMHANDLER__
#define __GAMEITEMHANDLER__

#include "GameTypes.h"

Item *CreateItem(const char *pName,const char *pImageName,ItemClickHandler pClickHandler);

void KeyClickHandler(Item *pKey);
void SwordClickHandler(Item *pSword);
void ShieldClickHandler(Item *pShield);
void HealpotClickHandler(Item *pHeal);
void ManapotClickHandler(Item *pMana);

#endif