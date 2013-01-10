#ifndef __GAMELEVELLOADER__
#define __GAMELEVELLOADER__

#include "GameTypes.h"

void LoadLevel(const char *pFileName);
void LoadItems(const char *pFileName);

Camera *CreateCamera(int iPosX,int iPosY,int iViewportWidth,int iViewportHeight);
Tile *CreateTile(int iPosX,int iPosY,const char *pImageFile,bool bCollidable);
GameHero *CreateHero(int iPosX,int iPosY);
LightSource *CreateLightSource(int iPosX,int iPosY);
Treasure *CreateTreasure(int iPosX,int iPosY);
Door *CreateDoor(int iPosX,int iPosY);
Enemy *CreateEnemy(int iPosX,int iPosY,int iStrength,int iDefense,int iHealth,const char *pImageFile,const char *pImageFileBattle);

#endif