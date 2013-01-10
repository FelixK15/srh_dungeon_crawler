#include "GameGlobals.h"

extern const int g_iHealthPotReg = 25;
extern const int g_iManaPotReg = 10;

const int g_iMaxTilex = 1000;
const int g_iMaxLightSources = 50;
const int g_iMaxTreasures = 50;
const int g_iMaxEnemies = 50;
const int g_iMaxDoors = 50;
const int g_iMaxTrigger = 10;

const int g_iMaxEquipment = 6;
const int g_iMaxItems = 10;

//constants for the player equipment
const int g_iBody = 0;
const int g_iLeftHand = 1;
const int g_iRightHand = 2;
const int g_iHead = 3;
const int g_iPants = 4;
const int g_iShoes = 5;

//Tile properties
const int g_iTileWidth = 32;
const int g_iTileHeight = 32;

int g_iAmountTiles = 0;
int g_iAmountLights = 0;
int g_iAmountTreasures = 0;
int g_iAmountEnemies = 0;
int g_iAmountDoors = 0;

int g_iIdleTime = 0;

//Level dimension
int g_iLevelHeight = 0;
int g_iLevelWidth = 0;

//All tiles are within this array.
Tile *g_pTiles[1000];

//All lightsources
LightSource *g_pLightSources[50];

//All treasures
Treasure *g_pTreasures[50];

//All enemies
Enemy *g_pEnemies[50];

//All doors
Door *g_pDoors[50];

//All Triggers
Trigger *g_pTriggers[10];

//The player
GameHero *g_pHero = NULL;

//Game Camera
Camera *g_pCamera = NULL;

//Fight Screen
FightScreen *g_pFightScreen = NULL;

//Game Messagebox
GameMessageBox *g_pMessageBox = NULL;

//Menu graphic
SRHGraphic *g_pMenuGraphic = NULL;

//Fog of war
SRHGraphic *g_pFogOfWar = NULL;