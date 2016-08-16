#include "SRHWindow.h"
#include "SRHExceptions.h"
#include "SRHGraphics.h"
#include "SRHGame.h"
#include "SRHGlobals.h"
#include "SRHIncludes.h"

#include "SRHGui.h"
#include "GameUpdateFunctions.h"
#include "GameDrawFunctions.h"

#include "GameTypes.h"
#include "GameGlobals.h"
#include "GameHandler.h"

#include "GameMouseFunctions.h"
#include "GameLevelLoader.h"

#include "GameMessageBox.h"
#include "GameKeyboardHandler.h"

#include <time.h>
#include <conio.h>

void LoadResources()
{
	DWORD dirLength = GetModuleFileNameA(0, g_ProcessDirectory, 255);

	for (int dirIndex = dirLength; dirIndex > 0; --dirIndex)
	{
		if (g_ProcessDirectory[dirIndex] == '\\')
		{
			g_ProcessDirectory[dirIndex] = 0;
			break;
		}
	}

	g_pMainMenuGraphic = SRHLoadGraphic("Images\\Menus\\mainmenu.bmp");
	g_pInstructions = SRHLoadGraphic("Images\\Menus\\instructions.bmp");

	g_pMainMenuGraphic->iPosX = g_pMainMenuGraphic->iPosY = 0;

	g_pButtons[0] = SRHCreateButton("Start","Images\\Buttons\\StartGame_Active.bmp",NULL,
		"Images\\Buttons\\StartGame_Focused.bmp",270,195,StartGame);

	g_pButtons[1] = SRHCreateButton("Instructions","Images\\Buttons\\Instructions_Active.bmp",NULL,
		"Images\\Buttons\\Instructions_Focused.bmp",270,300,ShowInstructions);

	g_pButtons[2] = SRHCreateButton("Quit","Images\\Buttons\\QuitGame_Active.bmp",NULL,
		"Images\\Buttons\\QuitGame_Focused.bmp",270,405,QuitGame);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR pCommandLine,int iCmdShow)
{
	int iReturn = 0;
	try
	{
		//Window gets created, level gets loaded, handler gets set.
		SRHCreateWindow(800,600,"SRH Dungeon Crawler",hInstance);
		LoadResources();

		g_pHandler.pMouseMoveHandler = MenuMouseMove;
		g_pHandler.pMouseLeftClickHandler = MenuMouseClick;
		g_pHandler.pDrawHandler = DrawMainMenu;
		g_pHandler.pQuitHandler = ReleaseResources;

		//We're ready to go. This function ends if the game closes.
		iReturn = SRHStartGame();
	}catch(SRHWindowsException e)
	{
		printf(e.what());
    _getch();
	}
	return iReturn;
}