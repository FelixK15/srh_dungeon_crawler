#include "GameLevelLoader.h"
#include "GameGlobals.h"
#include "SRHGlobals.h"

#include "GameMenuFunctions.h"
#include "GameItemHandler.h"
#include "GameTrigger.h"

#include <stdio.h>
#include <cstring>
#include <cerrno>
#include <time.h>
#include <cstdlib>

void LoadLevel( const char *pFileName )
{
	//This functions opens the level file and iterates through every single char within
	//the file.
	FILE *pFile = fopen(pFileName,"r");
	if(pFile == NULL){
		printf(strerror(errno));
	}else{
		char cChar = fgetc(pFile);
		char *pImageName = NULL;

		int iPosX = 0;
		int iPosY = 0;
		bool bCollidable = false;
		int iRandom = 0;
		srand(time(NULL));
		//Iterate through the file until EOF (End of file) is reached.
		while(cChar != EOF){
			if(cChar == '.'){

				iRandom = rand() % 10;
				if(iRandom <= 3){
					pImageName = "Images\\Tiles\\floor_1.bmp";
				}else if(iRandom <= 6){
					pImageName = "Images\\Tiles\\floor_2.bmp";
				}else if(iRandom <= 10){
					pImageName = "Images\\Tiles\\floor_3.bmp";
				}
				bCollidable = false;
			}else if(cChar == '|'){
				pImageName = "Images\\Tiles\\wall.bmp";
				bCollidable = true;
			}else if(cChar == '/'){
				pImageName = NULL;
				bCollidable = true;
			}else if(cChar == '\n'){
				iPosX = 0;
				iPosY += g_iTileHeight;
				cChar = fgetc(pFile);
				continue;
			}else if(cChar == '#'){
				pImageName = "Images\\Tiles\\door.bmp";
				bCollidable = true;
			}
			//current char + ".bmp" = filename.
			CreateTile(iPosX,iPosY,pImageName,bCollidable);

			iPosX += g_iTileWidth;

			//get the next char.
			cChar = fgetc(pFile);
		}

		fclose(pFile);

		//Save the level dimension
		g_iLevelWidth = g_pTiles[g_iAmountTiles - 1]->pGraphic->iPosX + g_pTiles[g_iAmountTiles - 1]->pGraphic->iWidth;
		g_iLevelHeight = g_pTiles[g_iAmountTiles - 1]->pGraphic->iPosY + g_pTiles[g_iAmountTiles - 1]->pGraphic->iHeight;

		g_pMenuGraphic = SRHLoadGraphic("Images\\Hero\\menu.bmp");
		g_pMenuGraphic->bVisible = true;
		g_pMenuGraphic->iPosX = g_iWidth - g_pMenuGraphic->iWidth;

		g_pCamera = CreateCamera(0,0,g_iWidth - g_pMenuGraphic->iWidth,g_iHeight);
		//g_pFightScreen = CreateFightScreen();

		g_pFogOfWar = SRHCreateGraphic(g_iWidth - 200,g_iHeight);
		g_pFogOfWar->cTransparent.R = 255;
		g_pFogOfWar->cTransparent.G = 255;
		g_pFogOfWar->cTransparent.B = 255;
	}
}

void LoadItems( const char *pFileName )
{
	FILE *pFile = fopen(pFileName,"r");
	if(pFile == NULL){
		printf(strerror(errno));
	}else{
		char cChar = fgetc(pFile);

		int iPosX = 0;
		int iPosY = 0;

		while(cChar != EOF){
			//l = lightsource
			if(cChar == 'l'){
				CreateLightSource(iPosX,iPosY);
			}else if(cChar == 'k'){
				//k = key
				Treasure *pTreasure = CreateTreasure(iPosX,iPosY);
				pTreasure->pItem = CreateItem("key","Images\\Items\\key.bmp",KeyClickHandler);
			}else if(cChar == 's'){
				//s = sword
				Treasure *pTreasure = CreateTreasure(iPosX,iPosY);
				pTreasure->pItem = CreateItem("sword","Images\\Items\\sword_item.bmp",SwordClickHandler);
			}else if(cChar == 'p'){
				//p = player

				//Load the player
				g_pHero = CreateHero(iPosX,iPosY);
			}else if(cChar == 'd'){
				//d = door
				CreateDoor(iPosX,iPosY);
			}else if(cChar == 'm'){
				//m = manapot
				Treasure *pTreasure = CreateTreasure(iPosX,iPosY);
				pTreasure->pItem = CreateItem("manapot","Images\\Items\\manapot.bmp",ManapotClickHandler);
			}else if(cChar == 'h'){
				//h = healthpot
				Treasure *pTreasure = CreateTreasure(iPosX,iPosY);
				pTreasure->pItem = CreateItem("healpot","Images\\Items\\healpot.bmp",HealpotClickHandler);
			}else if(cChar == 'e'){
				//e = enemy
				CreateEnemy(iPosX,iPosY,10,10,20,"Images\\Enemies\\guard.bmp","Images\\Enemies\\guard_big.bmp");
			}else if(cChar == '1'){
				//1 = trigger 1 (ExitTrigger)
				CreateTrigger(iPosX,iPosY,g_iTileWidth,g_iTileHeight,ExitTrigger);
			}else if(cChar == '2'){
				//2 = trigger 2 (GuardTrigger)
				CreateTrigger(iPosX,iPosY,g_iTileWidth,g_iTileHeight,GuardTrigger);
			}else if(cChar == 'a'){
				//a = shield
				Treasure *pTreasure = CreateTreasure(iPosX,iPosY);
				pTreasure->pItem = CreateItem("shield","Images\\Items\\shield_item.bmp",ShieldClickHandler);
			}

			iPosX += g_iTileWidth;

			if(cChar == '\n'){
				iPosX = 0;
				iPosY += g_iTileHeight;
			}

			cChar = fgetc(pFile);
		}

		fclose(pFile);
	}
}

Camera *CreateCamera( int iPosX,int iPosY,int iViewportWidth,int iViewportHeight )
{
	Camera *pCamera = NULL;
	if(g_pCamera != NULL){
		pCamera = g_pCamera;
	}else{
		pCamera = new Camera();
	}

	pCamera->iPosX = iPosX;
	pCamera->iPosY = iPosY;
	pCamera->iViewportHeight = iViewportHeight;
	pCamera->iViewportWidth = iViewportWidth;

	return pCamera;
}

Tile* CreateTile( int iPosX,int iPosY,const char *pImageFile,bool bCollidable )
{
	g_pTiles[g_iAmountTiles] = new Tile();
	g_pTiles[g_iAmountTiles]->iPosX = iPosX;
	g_pTiles[g_iAmountTiles]->iPosY = iPosY;
	g_pTiles[g_iAmountTiles]->bCollidable = bCollidable;
	g_pTiles[g_iAmountTiles]->iIndex = g_iAmountTiles;
	if(pImageFile){
		g_pTiles[g_iAmountTiles]->pGraphic = SRHLoadGraphic(pImageFile);
	}else{
		g_pTiles[g_iAmountTiles]->pGraphic = SRHCreateGraphic(g_iTileWidth,g_iTileHeight);
	}

	g_pTiles[g_iAmountTiles]->pGraphic->iPosX = iPosX;
	g_pTiles[g_iAmountTiles]->pGraphic->iPosY = iPosY;

	return g_pTiles[g_iAmountTiles++];
}

GameHero* CreateHero( int iPosX,int iPosY )
{
	GameHero *pHero = NULL;
	if(g_pHero != NULL){
		pHero = g_pHero;
	}else{
		pHero = new GameHero();
		g_pHero = pHero;

		pHero->pGraphic = SRHLoadGraphic("Images\\Hero\\hero.bmp");

		pHero->pLifeBar = SRHCreateGraphic(119,12);
		pHero->pManaBar = SRHCreateGraphic(119,12);

		pHero->iMaxHealth = pHero->iHealth = 100;
		pHero->iMaxMana = pHero->iMana = 50;

		pHero->pLifeBar->iPosX = 666;
		pHero->pLifeBar->iPosY = 48;

		pHero->pManaBar->iPosX = 666;
		pHero->pManaBar->iPosY = 72;

		pHero->iPosX = pHero->iPosY = 0;
		pHero->pGraphic->bVisible = true;
		pHero->iViewRadius = 150;

		//Equip the hero with pants and a shirt at the beginning.
		AddEquipment(g_iPants,0,3,"Images\\Items\\junk_pants_icon.bmp","Images\\Hero\\junk_pants.bmp");
		AddEquipment(g_iBody,0,3,"Images\\Items\\shirt_icon.bmp","Images\\Hero\\shirt.bmp");
	}

	pHero->iPosX = iPosX;
	pHero->iPosY = iPosY;

	return pHero;
}

LightSource* CreateLightSource( int iPosX,int iPosY )
{
	g_pLightSources[g_iAmountLights] = new LightSource();
	g_pLightSources[g_iAmountLights]->iIndex = g_iAmountLights;
	g_pLightSources[g_iAmountLights]->iPosX = iPosX;
	g_pLightSources[g_iAmountLights]->iPosY = iPosY;
	g_pLightSources[g_iAmountLights]->iViewRadius = 100;
	g_pLightSources[g_iAmountLights]->pGraphic = SRHLoadGraphic("Images\\Items\\lightsource.bmp");
	g_pLightSources[g_iAmountLights]->pGraphic->iPosX = iPosX;
	g_pLightSources[g_iAmountLights]->pGraphic->iPosY = iPosY;

	return g_pLightSources[g_iAmountLights++];
}

Treasure* CreateTreasure( int iPosX,int iPosY )
{
	g_pTreasures[g_iAmountTreasures] = new Treasure();
	g_pTreasures[g_iAmountTreasures]->iIndex = g_iAmountTreasures;
	g_pTreasures[g_iAmountTreasures]->iPosX = iPosX;
	g_pTreasures[g_iAmountTreasures]->iPosY = iPosY;
	g_pTreasures[g_iAmountTreasures]->bOpened = false;

	//Treasure closed graphic
	g_pTreasures[g_iAmountTreasures]->pGraphic[0] = SRHLoadGraphic("Images\\Items\\treasure.bmp");
	g_pTreasures[g_iAmountTreasures]->pGraphic[0]->iPosX = iPosX;
	g_pTreasures[g_iAmountTreasures]->pGraphic[0]->iPosY = iPosY;

	//Treasure opened graphic
	g_pTreasures[g_iAmountTreasures]->pGraphic[1] = SRHLoadGraphic("Images\\Items\\treasure_opened.bmp");
	g_pTreasures[g_iAmountTreasures]->pGraphic[1]->iPosX = iPosX;
	g_pTreasures[g_iAmountTreasures]->pGraphic[1]->iPosY = iPosY;
	
	return g_pTreasures[g_iAmountTreasures++];
}

Door* CreateDoor( int iPosX,int iPosY )
{
	g_pDoors[g_iAmountDoors] = new Door();
	g_pDoors[g_iAmountDoors]->iIndex = g_iAmountDoors;
	g_pDoors[g_iAmountDoors]->iPosX = iPosX;
	g_pDoors[g_iAmountDoors]->iPosY = iPosY;
	g_pDoors[g_iAmountDoors]->pTile = CreateTile(iPosX,iPosY,"Images\\Tiles\\door.bmp",true);

	return g_pDoors[g_iAmountDoors++];
}

Enemy * CreateEnemy( int iPosX,int iPosY,int iStrength,int iDefense,int iHealth,const char *pImageFile,const char *pImageFileBattle )
{
	g_pEnemies[g_iAmountEnemies] = new Enemy();
	g_pEnemies[g_iAmountEnemies]->iIndex = g_iAmountEnemies;
	g_pEnemies[g_iAmountEnemies]->iPosX = iPosX;
	g_pEnemies[g_iAmountEnemies]->iPosY = iPosY;
	g_pEnemies[g_iAmountEnemies]->iHealth = g_pEnemies[g_iAmountEnemies]->iMaxHealth = iHealth;
	g_pEnemies[g_iAmountEnemies]->iStrength = iStrength;
	g_pEnemies[g_iAmountEnemies]->iDefense = iDefense;
	g_pEnemies[g_iAmountEnemies]->pGraphic = SRHLoadGraphic(pImageFile);
	g_pEnemies[g_iAmountEnemies]->pFightGraphic = SRHLoadGraphic(pImageFileBattle);

	return g_pEnemies[g_iAmountEnemies++];
}
