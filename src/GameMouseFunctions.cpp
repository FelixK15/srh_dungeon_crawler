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

void MenuMouseClick( int iPosX,int iPosY )
{
	for(int i = 0;i < 10;++i){
		if(g_pButtons[i] != NULL){
			if(iPosX > g_pButtons[i]->iPosX && iPosX < g_pButtons[i]->iPosX + g_pButtons[i]->pGraphics[0]->iWidth){
				if(iPosY > g_pButtons[i]->iPosY && iPosY < g_pButtons[i]->iPosY + g_pButtons[i]->pGraphics[0]->iHeight){
					g_pButtons[i]->pHandler();
					break;
				}
			}
		}
	}
}

void MenuMouseMove( int iPosX,int iPosY )
{
	for(int i = 0;i < 10;++i){
		if(g_pButtons[i] != NULL){
			if(iPosX > g_pButtons[i]->iPosX && iPosX < g_pButtons[i]->iPosX + g_pButtons[i]->pGraphics[0]->iWidth){
				if(iPosY > g_pButtons[i]->iPosY && iPosY < g_pButtons[i]->iPosY + g_pButtons[i]->pGraphics[0]->iHeight){
					g_pButtons[i]->iCurrentState = SRHButton::iFocused;
					continue;
				}
			}

			g_pButtons[i]->iCurrentState = SRHButton::iActive;
		}
	}
}
