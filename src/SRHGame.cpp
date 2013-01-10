#include "SRHGame.h"
#include "SRHExceptions.h"
#include "SRHWindow.h"
#include "SRHGlobals.h"

UINT SRHStartGame()
{
	//If no window has been defined yet, an exception will be thrown.
	if(!g_pWindow){
		throw SRHNoWindowException();
	}

	//boolean that will get checked every frame.
	//Will be set to false if the player closes the window.
	bool bRunning = true;

	UINT iDeltaTime = 0;
	UINT iLast = 0;
	UINT iNow = GetTickCount();
	float fSeconds = 0.f;
	float fTimePerFrame = 1 / g_iFPS; //in seconds.
	DWORD dwDifferences = 0;
	MSG msg;

	while(bRunning){
		//Get the current message from the message stack.
		if(PeekMessage(&msg,g_pWindow,0,0,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//If the message was a quit message, stop the loop.
			if(msg.message == WM_QUIT){
				bRunning = false;
			}
		}else{
			//Get the current time and calculate the deltatime between the last and current frame.
			iNow = GetTickCount();
			iDeltaTime = iNow - iLast;

			//Call update and draw handler (if any exsits)
			if(g_pHandler.pUpdateHandler){
				g_pHandler.pUpdateHandler(iDeltaTime);
			}

			if(g_pHandler.pDrawHandler){
				g_pHandler.pDrawHandler();
			}
			
			//Convert the deltatime milliseconds to seconds.
			fSeconds = iDeltaTime / 1000;

			//If the current frame took longer than an average frame should take,
			//clamp the value.
			if(fSeconds > fTimePerFrame){
				fSeconds = fTimePerFrame;
			}else if(fSeconds < fTimePerFrame){
				//If the frame took less than an average frame, sleep the rest.
				dwDifferences = ((fTimePerFrame - fSeconds) * 1000);
				Sleep(dwDifferences);
			}

			iLast = iNow;
		}
	}

	//Close the window at the end of the loop.
	SRHCloseWindow();
	
	return msg.message;
}