#ifndef __SRH_WINDOW__
#define __SRH_WINDOW__

#include "SRHCustomTypes.h"

/**
 * Creates a new window with the specific width,height and title. This function also
 * creates the front-/ and backbuffer of the window to ensure double buffering.
 *
 * @note This function can throw SRHWindowAlreadyDefinedException.
 *
 * @param iWidth Width of the window.
 * @param iHeight Height of the window.
 * @param pTitle Title of the window.
 */
void SRHCreateWindow(const int iWidth,const int iHeight,const char *pTitle,HINSTANCE hInstance);

/**
 * Closes a window previously created with SRHCreateWindow().
 *
 * @note This function can throw SRHNoWindowException.
 */
void SRHCloseWindow();
#endif