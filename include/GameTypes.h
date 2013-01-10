#ifndef __GAMESPECIFICTYPES__
#define __GAMESPECIFICTYPES__

#include "SRHGraphics.h"

struct Item;

typedef void(*ItemClickHandler)(Item*);
typedef void(*TriggerHandler)();

struct GameMessageBox
{
	unsigned int iWidth;
	unsigned int iHeight;

	int iPosX;
	int iPosY;

	const char *pMessage;

	SRHGraphic *pGraphic;
};

struct Trigger
{
	unsigned int iWidth;
	unsigned int iHeight;

	int iPosX;
	int iPosY;

	TriggerHandler pHandler;
};

struct LightSource
{
	unsigned int iIndex;
	unsigned int iViewRadius;

	int iPosX;
	int iPosY;

	SRHGraphic *pGraphic;
};

struct Item
{
	unsigned int iIndex;

	const char *pName;

	SRHGraphic *pGraphic;

	ItemClickHandler pClickHandler;
};

struct Equipment
{
	unsigned int iStrength;
	unsigned int iDefense;

	SRHGraphic *pGraphicInventory;
	SRHGraphic *pGraphicOnPlayer;
};

struct Treasure
{
	unsigned int iIndex;

	Item *pItem;

	int iPosX;
	int iPosY;

	bool bOpened;

	SRHGraphic *pGraphic[2];
};

struct Enemy
{
	static const int iDefaultAttackCoolDown = 2500;

	unsigned int iDefense;
	unsigned int iStrength;
	unsigned int iMaxHealth;
	unsigned int iIndex;

	int iAttackCooldown;
	int iHealth;
	int iPosX;
	int iPosY;

	SRHGraphic *pGraphic;
	SRHGraphic *pFightGraphic;
};

struct GameHero
{
	static const int iDefaultAttackCoolDown = 1500;

	unsigned int iMaxHealth;
	unsigned int iMaxMana;
	unsigned int iStrength;
	unsigned int iDefense;
	unsigned int iViewRadius;

	SRHGraphic *pGraphic;
	SRHGraphic *pLifeBar;
	SRHGraphic *pManaBar;

	Equipment *pEquipment[6];
	Item *pItems[10];

	int iHealth;
	int iMana;
	int iPosX;
	int iPosY;
	int iPosXLastFrame;
	int iPosYLastFrame;	
	int iAttackCooldown;
};

//Tile struct that saves information such as graphic,
//if the tile has been discovered yet, if the tile is a
//neighbor of the player (e.g. is within the view volume)
//and if the tile is collidable.
struct Tile
{
	unsigned int iIndex;

	int iPosX;
	int iPosY;

	SRHGraphic *pGraphic;

	bool bCollidable;
};

struct Door
{
	unsigned int iIndex;

	int iPosX;
	int iPosY;

	Tile *pTile;
};

struct Camera
{
	int iPosX;
	int iPosY;
	int iViewportWidth;
	int iViewportHeight;
};

struct FightScreen
{
	SRHGraphic *pGraphic;
	SRHGraphic *pEnemyLifeBar;

	Enemy *pEnemy;
};

#endif