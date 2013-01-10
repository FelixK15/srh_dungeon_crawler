#include "GameMouseFunctions.h"
#include "GameGlobals.h"

#include "SRHWindow.h"


void ItemMouseClick( int iPosX,int iPosY )
{
	for(int i = 0;i < g_iMaxItems;++i){
		if(g_pHero->pItems[i] != NULL){
			Item *pItem = g_pHero->pItems[i];
			if(iPosX > pItem->pGraphic->iPosX && iPosX < pItem->pGraphic->iPosX + pItem->pGraphic->iWidth){
				if(iPosY > pItem->pGraphic->iPosY && iPosY < pItem->pGraphic->iPosY + pItem->pGraphic->iHeight){
					if(pItem->pClickHandler != NULL){
						pItem->pClickHandler(pItem);
					}
				}
			}
		}
	}
}
