#include "GameTrigger.h"
#include "SRHGlobals.h"

#include "GameUpdateFunctions.h"
#include "GameGlobals.h"
#include "GameMessageBox.h"
#include "GameKeyboardHandler.h"

Trigger * CreateTrigger( int iPosX,int iPosY,int iWidth,int iHeight,TriggerHandler pHandler )
{
	for(int i = 0;i < g_iMaxTrigger;++i){
		if(g_pTriggers[i] == NULL){
			g_pTriggers[i] = new Trigger();
			g_pTriggers[i]->iPosX = iPosX;
			g_pTriggers[i]->iPosY = iPosY;
			g_pTriggers[i]->iWidth = iWidth;
			g_pTriggers[i]->iHeight = iHeight;
			g_pTriggers[i]->pHandler = pHandler;

			return g_pTriggers[i];
		}
	}

	return NULL;
}

void ExitTrigger()
{
	g_pHandler.pUpdateHandler = UpdateMessagebox;
	g_pHandler.pKeyDownHandler = KeyboardHandlerMessageBox;
	g_pHero->iPosY += g_iTileHeight;
	g_pMessageBox = CreateMessageBox("I'll never get back to the prison. There has to be a way out of here...",200,200,200,75);
}

void GuardTrigger()
{
	if(g_pHero->iStrength < 10){
		g_pHandler.pUpdateHandler = UpdateMessagebox;
		g_pHandler.pKeyDownHandler = KeyboardHandlerMessageBox;
		g_pHero->iPosY -= g_iTileHeight;
		g_pMessageBox = CreateMessageBox("Maybe I shouldn't approach that guard without a weapon.",200,200,200,50);
	}
}
