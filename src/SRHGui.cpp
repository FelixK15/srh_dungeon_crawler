#include "SRHGui.h"
#include "SRHGraphics.h"
#include "SRHGlobals.h"

SRHButton *SRHCreateButton( const char* pCaption,const char* pBackgroundImage,const char* pInactiveImage,const char *pFocusedImage,
						   int iPosX,int iPosY,SRHButtonClickHandler pHandler )
{
	//Create a new SRHButton struct and fill in the provided data.
	SRHButton *pButton = new SRHButton();
	pButton->pCaption = pCaption;
	pButton->pHandler = pHandler;

	try{
		//Try to load the provided graphic.
		pButton->pGraphics[SRHButton::iActive] = pBackgroundImage != NULL ? SRHLoadGraphic(pBackgroundImage) : NULL;
		pButton->pGraphics[SRHButton::iInactive] = pInactiveImage != NULL ? SRHLoadGraphic(pInactiveImage) : NULL;
		pButton->pGraphics[SRHButton::iFocused] = pFocusedImage != NULL ? SRHLoadGraphic(pFocusedImage) : NULL;
	}catch(std::exception &e){
		//If the loading failed, delete the SRHButton struct and throw an exception.
		for(int i = 0;i < SRHButton::iAmountGraphics;++i){
			SAFE_DELETE(pButton->pGraphics[i]);
		}

		SAFE_DELETE(pButton);
		throw e;
	}
	
	//Set the position of the button.
	pButton->iPosX = iPosX;
	pButton->iPosY = iPosY;
	pButton->iCurrentState = SRHButton::iActive;

	return pButton;
}

void SRHDrawButton( SRHButton *pButton )
{
	if(pButton != NULL){
		if(pButton->pGraphics[pButton->iCurrentState] != NULL){
			pButton->pGraphics[pButton->iCurrentState]->iPosX = pButton->iPosX;
			pButton->pGraphics[pButton->iCurrentState]->iPosY = pButton->iPosY;

			SRHDrawGraphic(pButton->pGraphics[pButton->iCurrentState]);
		}
	}
}
