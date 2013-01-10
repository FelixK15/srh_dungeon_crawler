#include "SRHGlobals.h"

HWND g_pWindow = NULL;
HINSTANCE g_pInstance = NULL;
HDC g_pBackbufferDC = NULL;
HDC g_pFrontbufferDC = NULL;
HBITMAP g_pBackbufferBitmap = NULL;

SRHHandler g_pHandler;

std::list<SRHButton*> g_lButtons;
std::list<SRHGraphic*> g_lGraphics;
std::map<std::string,SRHGraphic*> _mLoadedGraphics;

int g_iWidth = 0;
int g_iHeight = 0;
float g_iFPS = 60.f;