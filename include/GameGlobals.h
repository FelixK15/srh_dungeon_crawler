#ifndef __GAMEGLOBALS__
#define __GAMEGLOBALS__

#include "GameTypes.h"

extern const int g_iHealthPotReg;
extern const int g_iManaPotReg;

extern const int g_iMaxTilex;
extern const int g_iMaxLightSources;
extern const int g_iMaxTreasures;
extern const int g_iMaxEnemies;
extern const int g_iMaxDoors;
extern const int g_iMaxTrigger;

extern const int g_iMaxEquipment;
extern const int g_iMaxItems;

//constants for the player equipment
extern const int g_iHead;
extern const int g_iLeftHand;
extern const int g_iRightHand;
extern const int g_iBody;
extern const int g_iPants;
extern const int g_iShoes;

//Width and height of a tile.
extern const int g_iTileWidth;
extern const int g_iTileHeight;

//Width and height of the level
extern int g_iLevelWidth;
extern int g_iLevelHeight;

extern int g_iIdleTime;

//All tiles are within this array.
extern Tile *g_pTiles[1000];

//All lightsources
extern LightSource *g_pLightSources[50];

//All treasures
extern Treasure *g_pTreasures[50];

//All enemies
extern Enemy *g_pEnemies[50];

//All doors
extern Door *g_pDoors[50];

//All triggers
extern Trigger *g_pTriggers[10];

//The player
extern GameHero *g_pHero;

//Game Camera
extern Camera *g_pCamera;

//Fight Screen
extern FightScreen *g_pFightScreen;

//Menu graphic
extern SRHGraphic *g_pMenuGraphic;
extern SRHGraphic *g_pMainMenuGraphic;

//Instruction graphic
extern SRHGraphic *g_pInstructions;

//Game Over graphic
extern SRHGraphic *g_pGameOverGraphic;
//Fog of war
extern SRHGraphic *g_pFogOfWar;

extern SRHButton *g_pButtons[10];

extern GameMessageBox *g_pMessageBox;

extern int g_iAmountTiles;
extern int g_iAmountLights;
extern int g_iAmountTreasures;
extern int g_iAmountEnemies;
extern int g_iAmountDoors;
extern int g_iAmountTrigger;


#endif