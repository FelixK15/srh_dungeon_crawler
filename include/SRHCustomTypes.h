#ifndef __SRH_CUSTOMTYPES__
#define __SRH_CUSTOMTYPES__

#include "SRHIncludes.h"

typedef void(*SRHFocusLostHandler)(void);
typedef void(*SRHFocusGainedHandler)(void);

typedef void(*SRHKeyDownHandler)(char);
typedef void(*SRHKeyUpHandler)(char);

typedef void(*SRHMouseMoveHandler)(int,int);
typedef void(*SRHMouseLeftClickHandler)(int,int);
typedef void(*SRHMouseRightClickHandler)(int,int);

typedef void(*SRHQuitHandler)();
typedef void(*SRHWindowCloseHandler)();

typedef void(*SRHButtonClickHandler)();

typedef void(*SRHEventHandler)(HWND,UINT,WPARAM,LPARAM);

typedef void(*SRHUpdateHandler)(unsigned int);
typedef void(*SRHDrawHandler)();

struct SRHHandler
{
	SRHFocusGainedHandler pFocusGainedHandler;
	SRHFocusLostHandler pFocusLostHandler;
	SRHKeyDownHandler pKeyDownHandler;
	SRHKeyUpHandler pKeyUpHandler;
	SRHMouseMoveHandler pMouseMoveHandler;
	SRHMouseLeftClickHandler pMouseLeftClickHandler;
	SRHMouseRightClickHandler pMouseRightClickHandler;
	SRHQuitHandler pQuitHandler;
	SRHWindowCloseHandler pWindowCloseHandler;
	SRHEventHandler pEventHandler;

	SRHUpdateHandler pUpdateHandler;
	SRHDrawHandler pDrawHandler;
};

struct SRHColor
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct SRHGraphic
{
	bool bVisible;
	int iWidth;
	int iHeight;
	int iPosX;
	int iPosY;

	SRHColor cTransparent;

	HDC pImageDC;
	HBITMAP pImage;
};


struct SRHButton
{
	const static int iActive = 0;
	const static int iInactive = 1;
	const static int iFocused = 2;
	const static int iAmountGraphics = 3;

	int iCurrentState;
	
	int iPosX;
	int iPosY;
	
	const char* pCaption;

	SRHGraphic *pGraphics[iAmountGraphics];
	SRHButtonClickHandler pHandler;
};

#endif