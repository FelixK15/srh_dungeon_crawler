#include "GameHandler.h"

#include "GameMessageBox.h"
#include "GameKeyboardHandler.h"
#include "GameMouseFunctions.h"
#include "GameMenuFunctions.h"
#include "GameUpdateFunctions.h"
#include "GameDrawFunctions.h"
#include "GameGlobals.h"
#include "GameMath.h"

#include "GameLevelLoader.h"

#include "SRHGlobals.h"
#include "SRHSound.h"

#include <time.h>

void MoveLeft()
{
	g_pHero->iPosX -= g_iTileWidth;
}

void MoveRight()
{
	g_pHero->iPosX += g_iTileWidth;
}

void MoveDown()
{
	g_pHero->iPosY += g_iTileHeight;
}

void MoveUp()
{
	g_pHero->iPosY -= g_iTileHeight;
}

void TryAttackEnemy()
{
	//Is there an enemy to attack?
	if(g_pFightScreen->pEnemy != NULL){
		Enemy *pEnemy = g_pFightScreen->pEnemy;

		SRHPlaySound("Sounds\\sword.wav");

		//Calculate the attack damage.
		int iAttackDamage = g_pHero->iStrength / pEnemy->iDefense;
		srand((unsigned int)time(NULL));
		iAttackDamage += (int)(rand() % g_pHero->iStrength*0.5);

		//Subtract the damage from the enemy health
		pEnemy->iHealth -= iAttackDamage;

		//Check if the enemy is dead.
		if(pEnemy->iHealth <= 0){
			SAFE_DELETE(pEnemy->pGraphic);
			SAFE_DELETE(pEnemy->pFightGraphic);
			int iIndex = pEnemy->iIndex;
			SAFE_DELETE(pEnemy);
			g_pEnemies[iIndex] = NULL;
			SRHPlaySound("Sounds\\hit.wav");
		}

		//Reset the attack cool down
		g_pHero->iAttackCooldown = GameHero::iDefaultAttackCoolDown;
	}
 }

void TryOpenTreasure()
{
	//iterate through all treasures
	for(int i = 0;i < g_iAmountTreasures;++i){
		if(g_pTreasures[i] != NULL){
			//Check for collision with a treasure
			if(g_pHero->iPosX == g_pTreasures[i]->iPosX && g_pHero->iPosY == g_pTreasures[i]->iPosY){
				//If a collision has been found, check if the treasure has been opened before.
				if(!g_pTreasures[i]->bOpened){
					//If not, set it to 'has been opened'...
					g_pTreasures[i]->bOpened = true;
					//...and add the item of the treasure to the players inventory.
					AddItem(g_pTreasures[i]->pItem);

					char cBuffer[80];
					sprintf(cBuffer,"Found %s",g_pTreasures[i]->pItem->pName);
					g_pMessageBox = CreateMessageBox(cBuffer,250,330,100,50);
					g_pHandler.pUpdateHandler = UpdateMessagebox;
					g_pHandler.pKeyDownHandler = KeyboardHandlerMessageBox;
				}
			}
		}
	}
}

void Update(UINT ms)
{
	CheckForCollision();
	UpdateEnemies(ms);
	UpdateHero(ms);
	UpdateCamera();
}

void Drawer()
{
	//The order of these calls is important.
	DrawTiles();			//First the pure map
	DrawLights();			//Then all light graphics (the torches)
	DrawTreasures();		//Then all the treasures
	DrawEnemies();			//Then all the enemies
	DrawFogOfWar();			//Calculate and draw the fog of war
	DrawHero();				//Draw the hero

	DrawInventory();		//Draw all the items of the player
	DrawHeroEquipment();	//Draw the equipment of the player in the menu
	DrawFightScreen();		//Try to draw the fight screen if a fight is going on
	DrawMessageBox();		//Draw the message box if there's a message to be drawn.
	SRHSwapBackbuffer();	//Swap the buffers.
}

void ReleaseResources()
{
	for(int i = 0;i < g_iMaxDoors;++i){
		SAFE_DELETE(g_pDoors[i]);
	}

	for(int i = 0;i < g_iMaxEnemies;++i){
		if(g_pEnemies[i] != NULL){
			SAFE_DELETE(g_pEnemies[i]->pGraphic);
			SAFE_DELETE(g_pEnemies[i]);
		}
	}

	for(int i = 0;i < g_iMaxTreasures;++i){
		if(g_pTreasures[i] != NULL){
			SAFE_DELETE(g_pTreasures[i]->pGraphic[0]);
			SAFE_DELETE(g_pTreasures[i]->pGraphic[1]);
		}

		SAFE_DELETE(g_pTreasures[i]);
	}


	if(g_pHero != NULL){
		for(int i = 0;i < g_iMaxItems;++i){
			if(g_pHero->pItems[i] != NULL){
				SAFE_DELETE(g_pHero->pItems[i]->pGraphic);
				SAFE_DELETE(g_pHero->pItems[i]);
			}
		}

		for(int i = 0;i < g_iMaxEquipment;++i){
			if(g_pHero->pEquipment[i] != NULL){
				SAFE_DELETE(g_pHero->pEquipment[i]->pGraphicInventory);
				SAFE_DELETE(g_pHero->pEquipment[i]->pGraphicOnPlayer);
				SAFE_DELETE(g_pHero->pEquipment[i]);
			}
		}
	}

	for(int i = 0;i < g_iAmountTiles;++i){
		if(g_pTiles[i] != NULL){
			SAFE_DELETE(g_pTiles[i]->pGraphic);
			SAFE_DELETE(g_pTiles[i]);
		}
	}

	if(g_pHero != NULL){
		SAFE_DELETE(g_pHero->pLifeBar);
		SAFE_DELETE(g_pHero->pManaBar);
		SAFE_DELETE(g_pHero->pGraphic);
		SAFE_DELETE(g_pHero);
	}

	if(g_pMenuGraphic != NULL){
		SAFE_DELETE(g_pMenuGraphic);
	}

	if(g_pFogOfWar != NULL){
		SAFE_DELETE(g_pFogOfWar);
	}

	if(g_pMessageBox != NULL){
		SAFE_DELETE(g_pMessageBox->pGraphic);
		SAFE_DELETE(g_pMessageBox);
	}

	g_iAmountTiles = g_iAmountTreasures = 0;
}

void StartGame()
{
	ReleaseResources();

	LoadLevel(".\\Data\\level.txt");
	LoadItems(".\\Data\\items.txt");

	g_pHandler.pDrawHandler = Drawer;
	g_pHandler.pUpdateHandler = Update;
	g_pHandler.pMouseLeftClickHandler = ItemMouseClick;
	g_pHandler.pMouseMoveHandler = NULL;
	g_pHandler.pKeyDownHandler = KeyboardHandlerMovement;

	g_pHero->iHealth = g_pHero->iMaxHealth;
	g_pHero->iMana = g_pHero->iMaxMana;

}

void QuitGame()
{
	PostMessage(g_pWindow,WM_CLOSE,0,0);
}

void ShowInstructions()
{
	g_pHandler.pKeyDownHandler = KeyboardHandlerGameover;
	g_pHandler.pDrawHandler = DrawInstructions;
	g_pHandler.pMouseLeftClickHandler = NULL;
	g_pHandler.pMouseMoveHandler = NULL;
}
