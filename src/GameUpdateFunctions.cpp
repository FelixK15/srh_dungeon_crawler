#include "GameUpdateFunctions.h"
#include "GameGlobals.h"

#include "SRHGlobals.h"
#include "GameHandler.h"

#include <time.h>

void CheckForCollision()
{
	//Check if the player is inside the level dimension
	if(g_pHero->iPosX < 0 || g_pHero->iPosX + g_pHero->pGraphic->iWidth > g_iLevelWidth)
	{
		g_pHero->iPosX = g_pHero->iPosXLastFrame;
	}

	if(g_pHero->iPosY < 0 || g_pHero->iPosY + g_pHero->pGraphic->iHeight > g_iLevelHeight)
	{
		g_pHero->iPosY = g_pHero->iPosYLastFrame;
	}

	//The loop checks for collisions.
	//If a collision happened, the player will be reset to his old position.
	for(int i = 0; i < g_iAmountTiles;++i){
		if(g_pTiles[i] != NULL){

			if(g_pTiles[i]->iPosX == g_pHero->iPosX && g_pTiles[i]->iPosY == g_pHero->iPosY){
				if(g_pTiles[i]->bCollidable){
					g_pHero->iPosX = g_pHero->iPosXLastFrame;
					g_pHero->iPosY = g_pHero->iPosYLastFrame;
					break;
				}			
			}
		}
	}

	//This loop checks for collisions with triggers.
	//If a collision happened, the triggers handler will be called.
	for(int i = 0;i < g_iMaxTrigger;++i){
		if(g_pTriggers[i] != NULL){
			if(g_pTriggers[i]->iPosX == g_pHero->iPosX && g_pTriggers[i]->iPosY == g_pHero->iPosY){
				g_pTriggers[i]->pHandler();
				break;
			}
		}
	}

	//Reset the current enemy of the fight screen.
	g_pFightScreen->pEnemy = NULL;

	//This loop checks for collisions with enemies.
	//If a collision happened, the fight screen gets loaded.
	for(int i = 0;i < g_iAmountEnemies;++i){
		if(g_pEnemies[i] != NULL){
			if(g_pEnemies[i]->iPosX == g_pHero->iPosX && g_pEnemies[i]->iPosY == g_pHero->iPosY){
				g_pFightScreen->pEnemy = g_pEnemies[i];
				break;
			}
		}
	}
}

void UpdateCamera()
{
	//Calculate the new position of the camera - so that the hero is always in the center of the camera.
	int iNewCameraPosX = 0;
	int iNewCameraPosY = 0;

	iNewCameraPosX = g_pHero->iPosX - g_pCamera->iViewportWidth*0.5;
	iNewCameraPosY = g_pHero->iPosY - g_pCamera->iViewportHeight*0.5;

	//Set the new camera position
	g_pCamera->iPosX = iNewCameraPosX;
	g_pCamera->iPosY = iNewCameraPosY;
}

void UpdateHero(unsigned int iMS)
{
	//Update the position of the player
	g_pHero->iPosXLastFrame = g_pHero->iPosX;
	g_pHero->iPosYLastFrame = g_pHero->iPosY;

	//Set the new hero graphic position.
	g_pHero->pGraphic->iPosX = g_pHero->iPosX;
	g_pHero->pGraphic->iPosY = g_pHero->iPosY;

	g_pHero->iDefense = g_pHero->iStrength = 0;

	for(int i = 0;i < g_iMaxEquipment;++i){
		if(g_pHero->pEquipment[i] != NULL){
			g_pHero->iStrength += g_pHero->pEquipment[i]->iStrength;
			g_pHero->iDefense += g_pHero->pEquipment[i]->iDefense;
		}
	}

	if(g_pHero->iAttackCooldown > 0){
		g_pHero->iAttackCooldown -= iMS;
	}
}

void UpdateEnemies( unsigned int iMS )
{
	for(int i = 0;i < g_iAmountEnemies;++i){
		if(g_pEnemies[i] != NULL){
			if(g_pEnemies[i]->iAttackCooldown > 0){
				g_pEnemies[i]->iAttackCooldown -= iMS;
			}
		}
	}

	if(g_pFightScreen->pEnemy != NULL){
		Enemy *pEnemy = g_pFightScreen->pEnemy;
		if(g_pFightScreen->pEnemy->iAttackCooldown <= 0){
			int iAttackDamage = pEnemy->iStrength / g_pHero->iDefense;
			srand(time(NULL));
			iAttackDamage += rand() % pEnemy->iStrength * 0.5;
			g_pHero->iHealth -= iAttackDamage;
			pEnemy->iAttackCooldown = Enemy::iDefaultAttackCoolDown;
		}
	}
}

void UpdateIdle(unsigned int iMS)
{
	g_iIdleTime -= iMS;

	if(g_iIdleTime <= 0){
		if(g_pMessageBox != NULL){
			SAFE_DELETE(g_pMessageBox->pGraphic);
			SAFE_DELETE(g_pMessageBox);
		}
		
		g_pHandler.pKeyDownHandler = KeyboardHandler;
		g_pHandler.pUpdateHandler = Update;
	}
}
