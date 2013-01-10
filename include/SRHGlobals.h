#ifndef __SRH_GLOBALS__
#define __SRH_GLOBALS__

#include "SRHIncludes.h"
#include "SRHCustomTypes.h"

#define SAFE_DELETE(pointer)  if(pointer != NULL){delete pointer;pointer = NULL;}

//Windows OS Resourcen
extern HWND g_pWindow;
extern HINSTANCE g_pInstance;
extern HDC g_pBackbufferDC;
extern HDC g_pFrontbufferDC;
extern HBITMAP g_pBackbufferBitmap;

extern SRHHandler g_pHandler;

//Internal lists
extern std::list<SRHButton*> g_lButtons;

//Settings
extern int g_iWidth;
extern int g_iHeight;
extern float g_iFPS;

#endif