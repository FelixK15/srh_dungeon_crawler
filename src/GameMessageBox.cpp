#include "GameMessageBox.h"
#include "SRHGlobals.h"

#include "windows.h"

GameMessageBox *CreateMessageBox( const char *pMessage,int iPosX,int iPosY,int iWidth,int iHeight )
{
	const int iAmountGraphics = 1500;

	SRHGraphic *pGraphics[iAmountGraphics] = {0};

	GameMessageBox *pMessageBox = new GameMessageBox();
	pMessageBox->pMessage = pMessage;
	pMessageBox->iPosX = iPosX;
	pMessageBox->iPosY = iPosY;
	pMessageBox->iWidth = iWidth;
	pMessageBox->iHeight = iHeight;

	SRHGraphic *pMessageBoxGraphic = SRHCreateGraphic(iWidth,iHeight);
	pMessageBoxGraphic->iPosX = iPosX;
	pMessageBoxGraphic->iPosY = iPosY;

	HBRUSH pBackgroundBrush = CreateSolidBrush(RGB(25,17,0));

	SelectObject(pMessageBoxGraphic->pImageDC,pBackgroundBrush);
	Rectangle(pMessageBoxGraphic->pImageDC,0,0,iWidth,iHeight);
	DeleteObject(pBackgroundBrush);

	pGraphics[0] = SRHLoadGraphic("Images\\MessageBox\\box_corner_left_top.bmp");
	pGraphics[0]->iPosX = 0;
	pGraphics[0]->iPosY = 0;

	pGraphics[1] = SRHLoadGraphic("Images\\MessageBox\\box_corner_right_top.bmp");
	pGraphics[1]->iPosX = iWidth - pGraphics[1]->iWidth;
	pGraphics[1]->iPosY = 0;

	pGraphics[2] = SRHLoadGraphic("Images\\MessageBox\\box_corner_left_bottom.bmp");
	pGraphics[2]->iPosX = 0;
	pGraphics[2]->iPosY = iHeight - pGraphics[2]->iHeight;

	pGraphics[3] = SRHLoadGraphic("Images\\MessageBox\\box_corner_right_bottom.bmp");
	pGraphics[3]->iPosX = iWidth - pGraphics[3]->iWidth;
	pGraphics[3]->iPosY = iHeight - pGraphics[3]->iHeight;

	int iCounter = 5;
	int x = 0;
	int y = 0;

	const int iBorderWidth = pGraphics[0]->iWidth;
	const int iBorderHeight = pGraphics[0]->iHeight;

	const int iPaddingX = 2;
	const int iPaddingY = 2;

	for(x = iBorderWidth,y = 0;x < (iWidth - iBorderWidth);++x,++iCounter){
		pGraphics[iCounter] = SRHLoadGraphic("Images\\MessageBox\\box_corner_horizontal.bmp");
		pGraphics[iCounter]->iPosX = x;
		pGraphics[iCounter]->iPosY = y;
	}

	for(x = iBorderWidth,y = (iHeight - iBorderHeight) + iPaddingY;x < (iWidth - iBorderWidth);++x,++iCounter){
		pGraphics[iCounter] = SRHLoadGraphic("Images\\MessageBox\\box_corner_horizontal.bmp");
		pGraphics[iCounter]->iPosX = x;
		pGraphics[iCounter]->iPosY = y;
	}

	for(y = iBorderWidth,x = 0;y < (iHeight - iBorderWidth);++y,++iCounter){
		pGraphics[iCounter] = SRHLoadGraphic("Images\\MessageBox\\box_corner_vertical.bmp");
		pGraphics[iCounter]->iPosX = x;
		pGraphics[iCounter]->iPosY = y;
	}

	for(y = iBorderWidth,x = (iWidth - iBorderWidth) + iPaddingX;y < (iHeight - iBorderWidth);++y,++iCounter){
		pGraphics[iCounter] = SRHLoadGraphic("Images\\MessageBox\\box_corner_vertical.bmp");
		pGraphics[iCounter]->iPosX = x;
		pGraphics[iCounter]->iPosY = y;
	}

	for(int i = 0;i < iCounter;++i){
		if(pGraphics[i] != NULL){
			TransparentBlt(pMessageBoxGraphic->pImageDC,pGraphics[i]->iPosX,pGraphics[i]->iPosY,pGraphics[i]->iWidth,pGraphics[i]->iHeight,
				pGraphics[i]->pImageDC,0,0,pGraphics[i]->iWidth,pGraphics[i]->iHeight,
				RGB(pGraphics[i]->cTransparent.R,pGraphics[i]->cTransparent.G,pGraphics[i]->cTransparent.B));

			SAFE_DELETE(pGraphics[i]);
		}
	}

	SetTextColor(pMessageBoxGraphic->pImageDC,RGB(255,255,255));
	SetBkColor(pMessageBoxGraphic->pImageDC,RGB(25,17,0));
	RECT rtTextRect = {0};
	rtTextRect.left = 5;
	rtTextRect.top = 5;
	rtTextRect.right = iWidth - 5;
	rtTextRect.bottom = iHeight - 5;

	DrawText(pMessageBoxGraphic->pImageDC,pMessage,-1,&rtTextRect,DT_WORDBREAK | DT_CENTER | DT_VCENTER);

	pMessageBox->pGraphic = pMessageBoxGraphic;

	return pMessageBox;
}
