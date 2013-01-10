#include "GameMenuFunctions.h"
#include "GameGlobals.h"

Item *GetItem( const char *pItemName )
{
	for(int i = 0;i < g_iMaxItems;++i){
		if(g_pHero->pItems[i] != NULL){
			const char *pName = g_pHero->pItems[i]->pName;
			if(strcmp(pName,pItemName) == 0){
				return g_pHero->pItems[i];
			}
		}
	}

	return NULL;
}

bool HasItem( const char *pItemName )
{
	return GetItem(pItemName) != NULL;
}

bool DeleteItem( const char *pItemName )
{
	for(int i = 0;i < g_iMaxItems;++i){
		Item *pItem = g_pHero->pItems[i];
		if(pItem != NULL){
			const char *pName = pItem->pName;
			if(strcmp(pName,pItemName) == 0){
				delete pItem->pGraphic;
				delete pItem;

				g_pHero->pItems[i] = NULL;
				return true;
			}
		}
	}

	return false;
}

void AddItem( Item *pItem )
{
	for(int i = 0;i < g_iMaxItems;++i){
		if(g_pHero->pItems[i] == NULL){
			g_pHero->pItems[i] = pItem;
			break;
		}
	}
}

void AddEquipment( int iPos,int iStrength,int iDefense,const char *pImageNameInventory,const char *pImageNameHero )
{
	if(iPos <= g_iMaxEquipment){
		Equipment *pEquipment = new Equipment();
		g_pHero->pEquipment[iPos] = pEquipment;
		pEquipment->iDefense = iDefense;
		pEquipment->iStrength = iStrength;
		try{
			pEquipment->pGraphicInventory = SRHLoadGraphic(pImageNameInventory);
			pEquipment->pGraphicOnPlayer = SRHLoadGraphic(pImageNameHero);
		}catch(std::exception e){
			DeleteEquipment(pEquipment);
		}
	}
}

bool DeleteEquipment( Equipment *pEquipment )
{
	for(int i = 0;i < g_iMaxEquipment;++i){
		if(g_pHero->pEquipment[i] == pEquipment){
			if(g_pHero->pEquipment[i]->pGraphicInventory != NULL){
				delete g_pHero->pEquipment[i]->pGraphicInventory;
				g_pHero->pEquipment[i]->pGraphicInventory = NULL;
			}

			if(g_pHero->pEquipment[i]->pGraphicOnPlayer != NULL){
				delete g_pHero->pEquipment[i]->pGraphicOnPlayer;
				g_pHero->pEquipment[i]->pGraphicOnPlayer = NULL;
			}

			delete g_pHero->pEquipment[i];
			g_pHero->pEquipment[i] = NULL;

			return true;
		}
	}

	return false;
}


