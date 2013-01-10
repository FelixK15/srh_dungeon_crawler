#ifndef __GAMEMENUFUNCTIONS__
#define __GAMEMENUFUNCTIONS__

#include "GameTypes.h"

Item *GetItem(const char *pItemName);
bool HasItem(const char *pItemName);
bool DeleteItem(const char *pItemName);
void AddItem(Item *pItem);

void AddEquipment(int iPos,int iStrength,int iDefense,const char *pImageNameInventory,const char *pImageNameHero);
bool DeleteEquipment(Equipment *pEquipment);

#endif