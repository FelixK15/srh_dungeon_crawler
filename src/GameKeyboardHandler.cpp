#include "GameKeyboardHandler.h"

#include "SRHGlobals.h"
#include "GameGlobals.h"
#include "GameHandler.h"

#include "GameDrawFunctions.h"
#include "GameKeyboardHandler.h"
#include "GameMouseFunctions.h"

#include <windows.h>


void KeyboardHandlerMovement( char cKey )
{
	//Controls:
	//Left = Move Left;
	//Right = Move Right;
	//Up = Move Up;
	//Down = Move Down;
	//Space = Attack / Open Treasure

	if(cKey == VK_LEFT){
		MoveLeft();
	}else if(cKey == VK_RIGHT){
		MoveRight();
	}else if(cKey == VK_UP){
		MoveUp();
	}else if(cKey == VK_DOWN){
		MoveDown();
	}else if(cKey == VK_SPACE){
		TryOpenTreasure();

		if(g_pHero->iAttackCooldown <= 0){
			TryAttackEnemy();
		}
	}
}

void KeyboardHandlerMessageBox( char cKey )
{
	if(cKey == VK_SPACE || cKey == VK_RETURN || cKey == VK_ESCAPE)
	{
		SAFE_DELETE(g_pMessageBox->pGraphic);
		SAFE_DELETE(g_pMessageBox);
	}
}

void KeyboardHandlerGameover( char cKey )
{
	if(cKey == VK_SPACE){
		g_pHandler.pDrawHandler = DrawMainMenu;
		g_pHandler.pMouseLeftClickHandler = MenuMouseClick;
		g_pHandler.pMouseMoveHandler = MenuMouseMove;
	}
}
