#include "GameItemHandler.h"
#include "GameGlobals.h"
#include "GameMenuFunctions.h"
#include "SRHExceptions.h"

Item *CreateItem(const char *pName,const char *pImageName,ItemClickHandler pClickHandler)
{
	Item *pItem = new Item();
	try{
		pItem->pName = pName;
		pItem->pGraphic = SRHLoadGraphic(pImageName);
		pItem->pClickHandler = pClickHandler;
	}catch(std::exception e){
		delete pItem;
		pItem = NULL;
	}

	return pItem;
}

void KeyClickHandler( Item *pKey )
{
	for(int i = 0;i < g_iMaxDoors;++i){
		Door *pDoor = g_pDoors[i];
		if(pDoor != NULL && pDoor->pTile->bCollidable){
			bool bNeighbour = false;

			if(g_pHero->iPosX + g_iTileWidth == pDoor->iPosX && g_pHero->iPosY == pDoor->iPosY){
				bNeighbour = true;
			}else if(g_pHero->iPosX - g_iTileWidth == pDoor->iPosX && g_pHero->iPosY == pDoor->iPosY){
				bNeighbour = true;
			}else if(g_pHero->iPosX == pDoor->iPosX && g_pHero->iPosY + g_iTileHeight == pDoor->iPosY){
				bNeighbour = true;
			}else if(g_pHero->iPosX == pDoor->iPosX && g_pHero->iPosY - g_iTileHeight == pDoor->iPosY){
				bNeighbour = true;
			}

			if(bNeighbour){
				DeleteItem(pKey->pName);
				pDoor->pTile->bCollidable = false;
				pDoor->pTile->pGraphic->bVisible = false;
			}
		}		
	}
}

void SwordClickHandler( Item *pSword )
{
	if(g_pHero->pEquipment[g_iLeftHand] != NULL){
		
	}else{
		AddEquipment(g_iLeftHand,10,0,"Images\\Items\\sword_icon.bmp","Images\\Hero\\sword.bmp");
		DeleteItem(pSword->pName);
	}
}


void ShieldClickHandler( Item *pShield )
{
	if(g_pHero->pEquipment[g_iRightHand] != NULL){

	}else{
		AddEquipment(g_iRightHand,10,0,"Images\\Items\\shield_icon.bmp","Images\\Hero\\shield.bmp");
		DeleteItem(pShield->pName);
	}
}


void HealpotClickHandler( Item *pHeal )
{
	g_pHero->iHealth += g_iHealthPotReg;
	if(g_pHero->iHealth > g_pHero->iMaxHealth){
		g_pHero->iHealth = g_pHero->iMaxHealth;
	}

	DeleteItem(pHeal->pName);
}

void ManapotClickHandler( Item *pMana )
{
	g_pHero->iMana += g_iManaPotReg;
	if(g_pHero->iMana > g_pHero->iMaxMana){
		g_pHero->iMana = g_pHero->iMaxMana;
	}

	DeleteItem(pMana->pName);
}
