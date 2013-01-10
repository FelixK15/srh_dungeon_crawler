#include "SRHGraphics.h"
#include "SRHGlobals.h"
#include "SRHExceptions.h"
#include "SRHIncludes.h"

// void SRHDrawGraphics()
// {
// 	if(!g_pWindow){
// 		throw SRHNoWindowException();
// 	}
// 
// 	PAINTSTRUCT psStruct;
// 	BeginPaint(g_pWindow,&psStruct);
// 	for(std::list<SRHGraphic*>::iterator iter = g_lGraphics.begin();iter != g_lGraphics.end();++iter){
// 		SRHGraphic *pGraphic = (*iter);
// 		if(pGraphic->pImageDC != NULL){
// 			BitBlt(g_pBackbufferDC,pGraphic->iPosX,pGraphic->iPosY,pGraphic->iWidth,pGraphic->iHeight,pGraphic->pImageDC,0,0,SRCCOPY);
// 		}
// 	}
// 
// 	g_lGraphics.clear();
// 	EndPaint(g_pWindow,&psStruct);
// }

//DEPRECATED
void SRHSwapBackbuffer()
{
	if(!g_pBackbufferDC){
		throw SRHNoWindowException();
	}

	BitBlt(g_pFrontbufferDC,0,0,g_iWidth,g_iHeight,g_pBackbufferDC,0,0,SRCCOPY);
	BitBlt(g_pBackbufferDC,0,0,g_iWidth,g_iHeight,NULL,0,0,BLACKNESS);
}

SRHGraphic *SRHLoadGraphic( std::string sImagePath )
{
	BITMAP btBitmapInfo;

	//Try to load a bitmap from the provided path.
	HBITMAP pBitmap = (HBITMAP)LoadImage(g_pInstance,sImagePath.c_str(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	//Check if the bitmap has been loaded successfully.
	//If not, an exception will be thrown.
	if(!pBitmap){
		throw SRHWindowsException(GetLastError());
	}
	
	//Get information about the bitmap (dimension,format,etc.)
	GetObject(pBitmap,sizeof(BITMAP),&btBitmapInfo);

	//Create a new SRHGraphic struct and fill it with data.
	SRHGraphic *pGraphic = new SRHGraphic();
	pGraphic->iWidth = btBitmapInfo.bmWidth;
	pGraphic->iHeight = btBitmapInfo.bmHeight;
	pGraphic->pImage = pBitmap;
	pGraphic->pImageDC = CreateCompatibleDC(NULL);
	pGraphic->bVisible = true;
	SelectObject(pGraphic->pImageDC,pBitmap);

	return pGraphic;
}

SRHGraphic *SRHCreateGraphic( int iWidth,int iHeight )
{
	BITMAP btBitmapInfo;

	//Try to create a bitmap with the given dimension.
	HBITMAP pBitmap = CreateCompatibleBitmap(g_pFrontbufferDC,iWidth,iHeight);

	//Check if the bitmap has been created successfully.
	//If not, an exception will be thrown.
	if(!pBitmap){
		throw SRHWindowsException(GetLastError());
	}

	//Get information about the bitmap (dimension,format,etc.)
	GetObject(pBitmap,sizeof(BITMAP),&btBitmapInfo);

	SRHGraphic *pGraphic = new SRHGraphic();
	pGraphic->iWidth = btBitmapInfo.bmWidth;
	pGraphic->iHeight = btBitmapInfo.bmHeight;
	pGraphic->pImage = pBitmap;
	pGraphic->pImageDC = CreateCompatibleDC(NULL);
	pGraphic->bVisible = true;
	
	SelectObject(pGraphic->pImageDC,pBitmap);

	return pGraphic;
}

void SRHDrawGraphic( SRHGraphic *pGraphic )
{
	//This function draws a given SRHGraphic.
	int iRGB = 0;

	//The graphic will only get drawn if it is
	//1. not NULL
	//2. visible
	//3. has a valid HDC
	if(pGraphic != NULL){
		if(pGraphic->bVisible){
			if(pGraphic->pImageDC != NULL){
				//Get the transparent color as 32bit int.
				iRGB = pGraphic->cTransparent.R;
				iRGB = (iRGB << 8) + pGraphic->cTransparent.G;
				iRGB = (iRGB << 8) + pGraphic->cTransparent.B;
				TransparentBlt(g_pBackbufferDC,pGraphic->iPosX,pGraphic->iPosY,pGraphic->iWidth,pGraphic->iHeight,pGraphic->pImageDC,0,0,pGraphic->iWidth,pGraphic->iHeight,iRGB);
	 			iRGB = 0;
			}
		}
	}
}
