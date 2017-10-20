#pragma comment(lib,"User32.lib")
#pragma comment(lib, "Gdi32.lib")
#define UNICODE
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "globals.h"
#include "shapes.h"
#include "eventhandler.h"

Shape shapes[3];
int currentShapeN = CIRCLE_N;

int circleUpdateMsg;
int squareUpdateMsg;
int triangleUpdateMsg;
int updateRequestMsg;


int WINAPI WinMain (HINSTANCE hThisInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpszArgument,
					int nCmdShow)
{
	srand(time(NULL));
	circleUpdateMsg = RegisterWindowMessage(L"PAIN_UPD_C");
	squareUpdateMsg = RegisterWindowMessage(L"PAIN_UPD_S");
	triangleUpdateMsg = RegisterWindowMessage(L"PAIN_UPD_T");
	updateRequestMsg = RegisterWindowMessage(L"PAIN_UPD_REQ");
	
	HDC hdc;
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */
	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = TEXT("Shapes");
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);
	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default color as the background of the window */
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx (&wincl))
		return 0;
		
	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx (
		   0,                   /* Extended possibilites for variation */
		   TEXT("Shapes"),         /* Classname */
		   "Shapes",       /* Title Text */
		   WS_OVERLAPPEDWINDOW, /* default window */
		   CW_USEDEFAULT,       /* Windows decides the position */
		   CW_USEDEFAULT,       /* were the window ends up on the screen */
		   PAIN_WIDTH-GetSystemMetrics(SM_CXSIZE), 	/* The programs width */
		   PAIN_HEIGHT,/* and height in pixels */
		   HWND_DESKTOP,        /* The window is a child-window to desktop */
		   NULL,                /* No menu */
		   hThisInstance,       /* Program Instance handler */
		   NULL                 /* No Window Creation data */
		   );	
	/* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
	
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
