#ifndef __SRH_GUI__
#define __SRH_GUI__

#include "SRHIncludes.h"
#include "SRHCustomTypes.h"

/**
 * Create a new SRHButton struct using this function and adds it
 * to an internally list so it is automaticaly drawn once you call SRHDrawButtons().
 * 
 * @note This function can throw SRHWindowsException.
 *
 * @param sCaption Caption of the button (Really used!)
 * @param sBackgroundImage The image of the button.
 * @param sInactiveImage The image of the button when it's inactive.
 * @param sFocusedImage The image of the button when it is focused.
 * @param x X Coordinate of the button.
 * @param y Y Coordinate of the button.
 * @param pHandler A callback function that is called when the button is pressed by a user.
 * 
 * @return SRHButton* Pointer to a SRHButton struct.
 */
SRHButton *SRHCreateButton(const char* pCaption,const char* pBackgroundImage,const char* pInactiveImage,const char *pFocusedImage,
                          int iPosX,int iPosY,SRHButtonClickHandler pHandler);

void SRHDrawButton(SRHButton *pButton);

#endif 