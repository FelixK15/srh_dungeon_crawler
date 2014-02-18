#include "SRHWindow.h"
#include "SRHExceptions.h"
#include "SRHGlobals.h"
#include "SRHGui.h"

#include <fcntl.h>
#include <time.h>
#include <io.h>

void SRHCreateConsole()
{
	//Create a new console
	AllocConsole();

	//Get the handle for the output of the console.
	int iStdOutHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);

	//Get a File object to the console output so we can set the standard output of the application
	//to the output of the console.
	FILE *pOutput = _fdopen(iStdOutHandle,"w");

	//Set the standard output of the application to the output of the console.
	//Whenever we call printf now, the text will be printed to the console.
	*stdout = *pOutput;

	printf("Debug console initialized...\n");
}

LRESULT CALLBACK SRHWndProc(HWND pHWND,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	//This function checks each message that the windows receives.
	if(iMessage == WM_DESTROY){
		//If the user choose the close the window, call the window close handler and post a WM_QUIT message.
		if(g_pHandler.pWindowCloseHandler){
			g_pHandler.pWindowCloseHandler();
		}

		PostQuitMessage(0);
		return 0;
	}else if(iMessage == WM_KILLFOCUS){
		//If the window lost its focus, call the focus lost handler.
		if(g_pHandler.pFocusLostHandler){
			g_pHandler.pFocusLostHandler();
		}
	}else if(iMessage == WM_SETFOCUS){
		//If the window gained focus, call the focus gained handler.
		if(g_pHandler.pFocusGainedHandler){
			g_pHandler.pFocusGainedHandler();
		}
	}else if(iMessage == WM_KEYDOWN){
		//If the user pressed a button - while the window had focus - the key down handler is called (pressed key as parameter)
		if(g_pHandler.pKeyDownHandler){
			g_pHandler.pKeyDownHandler((char)wParam);
		}
	}else if(iMessage == WM_KEYUP){
		//If the user released a button - while the window had focus - the key up handler is called (released key as parameter)
		if(g_pHandler.pKeyUpHandler){
			g_pHandler.pKeyUpHandler((char)wParam);
		}
	}else if(iMessage == WM_MOUSEMOVE){
		//If the user moved the mouse within the window, the mouse move handler is called (mouse x and y position as parameter)
		if(g_pHandler.pMouseMoveHandler){
			g_pHandler.pMouseMoveHandler(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		}
	}else if(iMessage == WM_LBUTTONDOWN){
		//If the user pressed the left mouse button within the window, the mouse left click handler is called (mouse x and y position as parameter)
		if(g_pHandler.pMouseLeftClickHandler){
			g_pHandler.pMouseLeftClickHandler(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		}
	}else if(iMessage == WM_RBUTTONDOWN){
		//If the user pressed the right mouse button within the window, the mouse right click handler is called (mouse x and y position as parameter)
		if(g_pHandler.pMouseRightClickHandler){
			g_pHandler.pMouseRightClickHandler(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		}
	}

	//The custom message handler is called.
	if(g_pHandler.pEventHandler){
		g_pHandler.pEventHandler(pHWND,iMessage,wParam,lParam);
	}

	return DefWindowProc(pHWND,iMessage,wParam,lParam);
}

void SRHCreateWindow(const int iWidth,const int iHeight,const char *pTitle,HINSTANCE hInstance)
{
	//If a window has been crated previously, throw an exception.
	if(g_pWindow){
		throw SRHWindowAlreadyDefinedException();
	}

	//If no HINSTANCE has been saved previously, save it now.
	if(!hInstance){
		hInstance = (HINSTANCE)GetModuleHandle(NULL);
	}

#ifdef _DEBUG
	SRHCreateConsole();
#endif

	g_pInstance = hInstance;

	RECT rWindowRect;
	rWindowRect.bottom = iHeight;
	rWindowRect.right = iWidth;
	rWindowRect.top = rWindowRect.left = 0;
	
	AdjustWindowRect(&rWindowRect,WS_OVERLAPPEDWINDOW,FALSE);

	//print debug information
	printf("Window rect:\nleft:%d\tright:%d\ttop:%d\tbottom:%d\n",
		rWindowRect.left,rWindowRect.right,rWindowRect.top,rWindowRect.bottom);

	//Create the window class.
	WNDCLASS wcClass;
	ZeroMemory(&wcClass,sizeof(WNDCLASS));
	wcClass.lpszClassName = "SRHGameWindow";
	wcClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcClass.lpfnWndProc = SRHWndProc;
	wcClass.hInstance = g_pInstance;

	//Register the class so we can create a window based on this class.
	RegisterClass(&wcClass);

	printf("Window class SRHGameWindow registered!\n");

	//Try to create the window. (If that failed, g_pWindow will be NULL)
	g_pWindow = CreateWindow("SRHGameWindow",pTitle,WS_OVERLAPPEDWINDOW,0,0,
		rWindowRect.right - rWindowRect.left,rWindowRect.bottom - rWindowRect.top,
		NULL,NULL,g_pInstance,NULL);

	//Check if the window has been created successfully.
	if(!g_pWindow){
		//If the window has not been created successfully, throw an exception.
		throw SRHWindowsException(GetLastError());
	}else{
		//If the window has been created successfully, show the window
		//and save the height and width of the window.
		ShowWindow(g_pWindow,5);
		SetForegroundWindow(g_pWindow);
		SetFocus(g_pWindow);

		printf("Window created!\n");

		g_iHeight = iHeight;
		g_iWidth = iWidth;

		//Create front- and backbuffer of the window for double buffering.
		g_pFrontbufferDC = GetDC(g_pWindow);
		g_pBackbufferDC = CreateCompatibleDC(NULL);
		g_pBackbufferBitmap = CreateCompatibleBitmap(g_pFrontbufferDC,iWidth,iHeight);
		SelectObject(g_pBackbufferDC,g_pBackbufferBitmap);

		//Background of the backbuffer is transparent, so that we can draw text without problems.
		SetBkColor(g_pBackbufferDC,TRANSPARENT);

		ZeroMemory(&g_pHandler,sizeof(SRHHandler));
	}
}

void SRHCloseWindow()
{
	//if no window has been created previously, throw an exception.
	if(!g_pWindow){
		throw SRHNoWindowException();
	}

	//if the window can't be closed, throw an exception.
	if(!CloseWindow(g_pWindow)){
		throw SRHWindowsException(GetLastError());
	}

	//Unregister the class, we registered during SRHCreateWindow().
	UnregisterClass("SRHGameWindow",NULL);

	printf("Window closed and class unregistered\n");
}