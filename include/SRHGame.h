#ifndef __SRH_GAME__
#define __SRH_GAME__

#include "SRHIncludes.h"

/**
* This functions starts the game and calls the update and draw handler
* from the global g_pHandler struct.
* @note The function doesn't return until the player closes the window.
*
* @return UINT The last message from the message loop (usually WM_QUIT)
*/
UINT SRHStartGame();

#endif 