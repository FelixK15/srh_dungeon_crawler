#ifndef __SRH_GRAPHICS__
#define __SRH_GRAPHICS__

#include "SRHIncludes.h"
#include "SRHCustomTypes.h"

/**
 * Swap back-/ and frontbuffer. Needs to be called once per frame 
 * to refresh content of the window. (Is called internally?)
 *
 * @note This function can throw SRHNoWindowException.
 */
void SRHSwapBackbuffer();

/**
 * Tries to load an image from the specific path.
 * Once an image has been loaded, it will get saved internally.
 *
 * So if you try to call SRHLoadGraphics() with a path to an image
 * that has been loaded before, the function will return a pointer
 * to the previously saved SRHGraphic.
 *
 * @note This function can throw SRHWindowsException.
 * @param pImagePath Path to the image.
 * 
 * @return SRHGraphic* Pointer to a SRHGraphic struct.
 */
SRHGraphic *SRHLoadGraphic(std::string pImagePath);

/**
 * Tries to create a new graphic with the given dimension.
 * The content of the graphic will be undefined, until you fill it.
 *
 * @note This function can throw SRHWindowsException.
 * @param iWidth Width of the graphic
 * @param iHeight Height of the graphic
 *
 * @return SRHGraphic* Pointer to a SRHGraphic struct.
 */
SRHGraphic *SRHCreateGraphic(int iWidth,int iHeight);

/**
 * Draw the graphic.
 *
 * @note The images will only be drawn if they're not NULL and if bVisible is true.
 *		 The images will be drawn in the order you call SRHDrawGraphic().
 *
 * @param pGraphic Pointer to a SRHGraphic struct.
 */
void SRHDrawGraphic(SRHGraphic *pGraphic);

#endif