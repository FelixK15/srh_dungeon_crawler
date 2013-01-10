#include "SRHWindow.h"
#include "SRHExceptions.h"
#include "SRHGraphics.h"
#include "SRHGame.h"
#include "SRHGlobals.h"
#include "SRHIncludes.h"

#include "SRHGui.h"

#include "GameTypes.h"
#include "GameGlobals.h"
#include "GameHandler.h"

#include "GameMouseFunctions.h"
#include "GameLevelLoader.h"

#include "GameMessageBox.h"

#include <time.h>

int main()
{
	//Brightness
	//exit code.
	//memory tracker?
	int iReturn = 0;
	try
	{
		//Window gets created, level gets loaded, handler gets set.
		SRHCreateWindow(800,600,"TEST");
		LoadLevel("Data\\level.txt");
		LoadItems("Data\\items.txt");
		g_pHandler.pMouseLeftClickHandler = ItemMouseClick;
		g_pHandler.pDrawHandler = Drawer;
		g_pHandler.pKeyDownHandler = KeyboardHandler;
		g_pHandler.pUpdateHandler = Update;
		g_pHandler.pQuitHandler = ReleaseResources;
		
		g_pHero->iHealth = 20;
		g_pHero->iMana = 10;

		g_pFightScreen = new FightScreen();
		g_pFightScreen->pEnemy = NULL;
		g_pFightScreen->pEnemyLifeBar = NULL;
		g_pFightScreen->pGraphic = SRHLoadGraphic("Images\\Hero\\fightscreen.bmp");
		g_pFightScreen->pGraphic->iPosX = 400;
		g_pFightScreen->pGraphic->iPosY = 0;

		//We're ready to go. This function ends if the game closes.
		iReturn = SRHStartGame();
	}catch(SRHWindowsException e)
	{
		printf(e.what());
	}
	std::system("PAUSE");
	return iReturn;
}