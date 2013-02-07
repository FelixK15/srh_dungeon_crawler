#include "GameDrawFunctions.h"
#include "GameGlobals.h"

#include "SRHGlobals.h"
#include "SRHGui.h"

#include "windows.h"

void DrawTiles()
{
	//Iterate trough all tiles and draw them based on 2 things.
	//1. Has the tile been discovered yet? (no - draw black; yes - draw transparent
	//2. Is the tile within the view distance of the player? (draw opaque)
	for(int i = 0;i < g_iAmountTiles;++i){
		if(g_pTiles[i] != NULL){	

			//Change position based on the camera.
			g_pTiles[i]->pGraphic->iPosX = g_pTiles[i]->iPosX - g_pCamera->iPosX;
			g_pTiles[i]->pGraphic->iPosY = g_pTiles[i]->iPosY - g_pCamera->iPosY;		

			//Check if the tile is within the view frustum of the camera
			if(g_pTiles[i]->pGraphic->iPosX >= 0 && 
				g_pTiles[i]->pGraphic->iPosX + g_pTiles[i]->pGraphic->iWidth <= g_pCamera->iViewportWidth &&
				g_pTiles[i]->pGraphic->iPosY >= 0 &&
				g_pTiles[i]->pGraphic->iPosY + g_pTiles[i]->pGraphic->iWidth <= g_pCamera->iViewportWidth){	

					SRHDrawGraphic(g_pTiles[i]->pGraphic);
			}
		}
	}
}

void DrawLights()
{
	for(int i = 0;i < g_iAmountLights;++i){
		if(g_pLightSources[i] != NULL){
			//Change position based on the camera.
			g_pLightSources[i]->pGraphic->iPosX = g_pLightSources[i]->iPosX - g_pCamera->iPosX;
			g_pLightSources[i]->pGraphic->iPosY = g_pLightSources[i]->iPosY - g_pCamera->iPosY;

			SRHDrawGraphic(g_pLightSources[i]->pGraphic);
		}
	}
}

void DrawTreasures()
{
	for(int i = 0;i < g_iAmountTreasures;++i){
		if(g_pTreasures[i] != NULL){
			//Change position based on the camera.
			g_pTreasures[i]->pGraphic[0]->iPosX = g_pTreasures[i]->iPosX - g_pCamera->iPosX;
			g_pTreasures[i]->pGraphic[0]->iPosY = g_pTreasures[i]->iPosY - g_pCamera->iPosY;

			g_pTreasures[i]->pGraphic[1]->iPosX = g_pTreasures[i]->iPosX - g_pCamera->iPosX;
			g_pTreasures[i]->pGraphic[1]->iPosY = g_pTreasures[i]->iPosY - g_pCamera->iPosY;

			//If the treasure has been opened, draw graphic 1, if not draw graphic 0
			if(g_pTreasures[i]->bOpened){
				SRHDrawGraphic(g_pTreasures[i]->pGraphic[1]);
			}else{
				SRHDrawGraphic(g_pTreasures[i]->pGraphic[0]);
			}
		}
	}
}

void DrawEnemies()
{
	for(int i = 0;i < g_iAmountEnemies;++i){
		if(g_pEnemies[i] != NULL){
			//Change position based on the camera.
			g_pEnemies[i]->pGraphic->iPosX = g_pEnemies[i]->iPosX - g_pCamera->iPosX;
			g_pEnemies[i]->pGraphic->iPosY = g_pEnemies[i]->iPosY - g_pCamera->iPosY;

			SRHDrawGraphic(g_pEnemies[i]->pGraphic);
		}
	}
}

void DrawFogOfWar()
{
	//Select the black pen and black brush to draw the "shadow"
	//pen = border
	//brush = rectangle itself
	SelectObject(g_pFogOfWar->pImageDC,GetStockObject(BLACK_PEN));
	SelectObject(g_pFogOfWar->pImageDC,GetStockObject(BLACK_BRUSH));

	//Draw everything black - "shadow"
	Rectangle(g_pFogOfWar->pImageDC,0,0,600,600);

	//Select the white pen white brush. The white pen and brush will be
	//handled as transparent.
	SelectObject(g_pFogOfWar->pImageDC,GetStockObject(WHITE_BRUSH));
	SelectObject(g_pFogOfWar->pImageDC,GetStockObject(WHITE_PEN));

	int iCenterX = 0;
	int iCenterY = 0;

	//go through each light source and calculate its center position.
	for(int i = 0;i < g_iAmountLights;++i){
		if(g_pLightSources[i] != NULL){
			//Center position will be calculated by the position of the GRAPHIC.That is because the graphic has already
			//been shifted by the camera previously.
			iCenterX = g_pLightSources[i]->pGraphic->iPosX + (int)(g_pLightSources[i]->pGraphic->iWidth*0.5);
			iCenterY = g_pLightSources[i]->pGraphic->iPosY + (int)(g_pLightSources[i]->pGraphic->iHeight*0.5);

			//The light ellipse of the light source will get drawn.
			Ellipse(g_pFogOfWar->pImageDC,iCenterX - (int)(g_pLightSources[i]->iViewRadius*0.5),
										  iCenterY - (int)(g_pLightSources[i]->iViewRadius*0.5),
										  iCenterX + (int)(g_pLightSources[i]->iViewRadius*0.5),
										  iCenterY + (int)(g_pLightSources[i]->iViewRadius*0.5));
		}
	}

	//Calculate the center position of the hero.
	iCenterX = (g_pHero->iPosX - g_pCamera->iPosX) + (int)(g_pHero->pGraphic->iWidth*0.5);
	iCenterY = (g_pHero->iPosY - g_pCamera->iPosY) + (int)(g_pHero->pGraphic->iHeight*0.5);

	//The view ellipse of the player gets drawn here.
	Ellipse(g_pFogOfWar->pImageDC,iCenterX - (int)(g_pHero->iViewRadius*0.5),
								  iCenterY - (int)(g_pHero->iViewRadius*0.5),
								  iCenterX + (int)(g_pHero->iViewRadius*0.5),
								  iCenterY + (int)(g_pHero->iViewRadius*0.5));

	//Draw the "fog of war"
	SRHDrawGraphic(g_pFogOfWar);
}

void DrawHero()
{
	//Update the player graphic based on the camera position.
	g_pHero->pGraphic->iPosX = g_pHero->iPosX - g_pCamera->iPosX;
	g_pHero->pGraphic->iPosY = g_pHero->iPosY - g_pCamera->iPosY;

	//Draw the player.
	SRHDrawGraphic(g_pHero->pGraphic);

	//Draw the menu.
	SRHDrawGraphic(g_pMenuGraphic);

	//Create the brushes for the life and mana bar of the player
	HBRUSH pLifeBrush = CreateSolidBrush(RGB(255,0,0));
	HBRUSH pManaBrush = CreateSolidBrush(RGB(0,0,255));

	//Calculate the length of the life and mana bar - based on the players health and mana
	float fWidthOfOneHP = (float)g_pHero->pLifeBar->iWidth / (float)g_pHero->iMaxHealth;
	float fWidthOfHPBar = (float)g_pHero->iHealth * fWidthOfOneHP;

	float fWidthOfOneMana = (float)g_pHero->pManaBar->iWidth / (float)g_pHero->iMaxMana;
	float fWidthOfManaBar = (float)g_pHero->iMana * fWidthOfOneMana;

	//Overdraw the old healthbar with black so we can fill it afterwards.
	SelectObject(g_pHero->pLifeBar->pImageDC,GetStockObject(BLACK_BRUSH));
	Rectangle(g_pHero->pLifeBar->pImageDC,0,0,g_pHero->pLifeBar->iWidth,g_pHero->pLifeBar->iHeight);

	//Overdraw the old manmbar with black so we can fill it afterwards.
	SelectObject(g_pHero->pManaBar->pImageDC,GetStockObject(BLACK_BRUSH));
	Rectangle(g_pHero->pManaBar->pImageDC,0,0,g_pHero->pManaBar->iWidth,g_pHero->pManaBar->iHeight);

	//Select the red life brush and draw a rectangle with it in the lifebar DC from the player
	SelectObject(g_pHero->pLifeBar->pImageDC,pLifeBrush);
	Rectangle(g_pHero->pLifeBar->pImageDC,0,0,(int)fWidthOfHPBar,g_pHero->pLifeBar->iHeight);

	//Select the blue mana brush and draw a rectangle with it in the mana DC from the player
	SelectObject(g_pHero->pManaBar->pImageDC,pManaBrush);
	Rectangle(g_pHero->pManaBar->pImageDC,0,0,(int)fWidthOfManaBar,g_pHero->pManaBar->iHeight);

	//Delete the brushes
	DeleteObject(pLifeBrush);
	DeleteObject(pManaBrush);

	//Draw the life and mana bar
	SRHDrawGraphic(g_pHero->pLifeBar);
	SRHDrawGraphic(g_pHero->pManaBar);

	//Draw the equipment based on their usage.
	for(int i = 0;i < g_iMaxEquipment;++i){
		if(g_pHero->pEquipment[i] != NULL){
			int iPosX = 0;
			int iPosY = 0;

			if(i == g_iHead){
				iPosX = 11;
				iPosY = 1;
			}else if(i == g_iLeftHand){
				iPosX = 4;
				iPosY = 2;
			}else if(i == g_iRightHand){
				iPosX = 21;
				iPosY = 10;
			}else if(i == g_iBody){
				iPosX = 9;
				iPosY = 11;
			}else if(i == g_iPants){
				iPosX = 11;
				iPosY = 21;
			}else if(i == g_iShoes){
				iPosX = 11;
				iPosY = 28;
			}

			//Calculate the position of the equipment relative to the position of the hero.
			g_pHero->pEquipment[i]->pGraphicOnPlayer->iPosX = g_pHero->pGraphic->iPosX + iPosX;
			g_pHero->pEquipment[i]->pGraphicOnPlayer->iPosY = g_pHero->pGraphic->iPosY + iPosY;

			//Draw the pGraphicOnPlayer graphic.
			SRHDrawGraphic(g_pHero->pEquipment[i]->pGraphicOnPlayer);
		}
	}
}

void DrawInventory()
{
	int iPadding = 2;
	int iPosX = 628;
	int iPosY = 140;

	//iterator through each item in the inventory and draw it.
	for(int i = 0;i < g_iMaxItems;++i){
		if(g_pHero->pItems[i] != NULL){
			g_pHero->pItems[i]->pGraphic->iPosX = iPosX + iPadding;
			g_pHero->pItems[i]->pGraphic->iPosY = iPosY + iPadding;

			//If the current position of the item in the inventory is divisible by 4,
			//shift the position down to the next row by increasing the y position
			//and resetting the x position.
			if(i % 4 == 0 && i != 0){
				iPosY += g_pHero->pItems[i]->pGraphic->iHeight + iPadding;
				iPosX = 628;
			}else{
				//If the position of the item is NOT divisible by 4, increase it's x position.
				iPosX += g_pHero->pItems[i]->pGraphic->iWidth + iPadding;
			}

			//Draw the item graphic.
			SRHDrawGraphic(g_pHero->pItems[i]->pGraphic);
		}
	}
	char pBuffer[10] = {0};
	RECT rtTextRect = {0};
	rtTextRect.left = 684;
	rtTextRect.bottom = 580;
	rtTextRect.top = 557;
	rtTextRect.right = 706;

	SetTextColor(g_pBackbufferDC,RGB(179,173,173));
	DrawText(g_pBackbufferDC,itoa(g_pHero->iStrength,pBuffer,10),-1,&rtTextRect,0);

	rtTextRect.left = 769;
	rtTextRect.right = 791;

	DrawText(g_pBackbufferDC,itoa(g_pHero->iDefense,pBuffer,10),-1,&rtTextRect,0);
}

void DrawHeroEquipment()
{
	int iPosX = 0;
	int iPosY = 0;

	//Draw the equipment in the menu based fixed position values based on
	//the usage of the equipment.
	for(int i = 0;i < g_iMaxEquipment;++i){
		if(g_pHero->pEquipment[i] != NULL){
			if(i == g_iHead){
				iPosX = 676;
				iPosY = 346;
			}else if(i == g_iLeftHand){
				iPosX = 626;
				iPosY = 396;
			}else if(i == g_iRightHand){
				iPosX = 726;
				iPosY = 396;
			}else if(i == g_iBody){
				iPosX = 676;
				iPosY = 396;
			}else if(i == g_iPants){
				iPosX = 676;
				iPosY = 446;
			}else if(i == g_iShoes){
				iPosX = 676;
				iPosY = 496;
			}

			g_pHero->pEquipment[i]->pGraphicInventory->iPosX = iPosX;
			g_pHero->pEquipment[i]->pGraphicInventory->iPosY = iPosY;
			
			//Draw the pGraphicInventory graphic
			SRHDrawGraphic(g_pHero->pEquipment[i]->pGraphicInventory);
		}
	}
}

void DrawMessageBox()
{
	if(g_pMessageBox != NULL){
		if(g_pMessageBox->pGraphic != NULL){
			SRHDrawGraphic(g_pMessageBox->pGraphic);
		}
	}
}

void DrawFightScreen()
{
	if(g_pFightScreen->pEnemy != NULL){
		Enemy *pEnemy = g_pFightScreen->pEnemy;
		pEnemy->pFightGraphic->iPosX = g_pFightScreen->pGraphic->iPosX + 6;
		pEnemy->pFightGraphic->iPosY = g_pFightScreen->pGraphic->iPosY + 6;

		if(g_pFightScreen->pEnemyLifeBar == NULL){
			g_pFightScreen->pEnemyLifeBar = SRHCreateGraphic(119,12);
			g_pFightScreen->pEnemyLifeBar->iPosX = g_pFightScreen->pGraphic->iPosX + 64;
			g_pFightScreen->pEnemyLifeBar->iPosY = g_pFightScreen->pGraphic->iPosY + 148;
		}

		SelectObject(g_pFightScreen->pEnemyLifeBar->pImageDC,GetStockObject(BLACK_BRUSH));
		Rectangle(g_pFightScreen->pEnemyLifeBar->pImageDC,0,0,g_pFightScreen->pEnemyLifeBar->iWidth,g_pFightScreen->pEnemyLifeBar->iHeight);

		HBRUSH pLifeBarBrush = CreateSolidBrush(RGB(255,0,0));
		
		float fWidthOfOneHP = (float)g_pFightScreen->pEnemyLifeBar->iWidth / (float)pEnemy->iMaxHealth;
		float fWidthOfHPBar = fWidthOfOneHP * (float)pEnemy->iHealth;
		
		SelectObject(g_pFightScreen->pEnemyLifeBar->pImageDC,pLifeBarBrush);
		Rectangle(g_pFightScreen->pEnemyLifeBar->pImageDC,0,0,(int)fWidthOfHPBar,g_pFightScreen->pEnemyLifeBar->iHeight);
		DeleteObject(pLifeBarBrush);

		RECT rtTextRect = {0};
		rtTextRect.left =  87;
		rtTextRect.top = 171;
		rtTextRect.right = rtTextRect.left + 20;
		rtTextRect.bottom = rtTextRect.top + 18;

		char pBuffer[10];

		SetBkColor(g_pFightScreen->pGraphic->pImageDC,RGB(0,0,0));
		SetTextColor(g_pFightScreen->pGraphic->pImageDC,RGB(179,173,173));
		DrawText(g_pFightScreen->pGraphic->pImageDC,itoa(pEnemy->iStrength,pBuffer,10),-1,&rtTextRect,0);

		rtTextRect.left += 83;
		rtTextRect.right += 83;

		DrawText(g_pFightScreen->pGraphic->pImageDC,itoa(pEnemy->iDefense,pBuffer,10),-1,&rtTextRect,0);
		SRHDrawGraphic(g_pFightScreen->pGraphic);
		SRHDrawGraphic(pEnemy->pFightGraphic);
		SRHDrawGraphic(g_pFightScreen->pEnemyLifeBar);
	}
}

void DrawMainMenu()
{
	SRHDrawGraphic(g_pMainMenuGraphic);

	for(int i = 0;i < 10;++i){
		if(g_pButtons[i] != NULL){
			SRHDrawButton(g_pButtons[i]);
		}
	}

	SRHSwapBackbuffer();
}

void DrawGameOver()
{
	SRHDrawGraphic(g_pGameOverGraphic);
	SRHSwapBackbuffer();
}

void DrawInstructions()
{
	SRHDrawGraphic(g_pInstructions);
	SRHSwapBackbuffer();
}
