#include "globals.h"

double scale = 1;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
	HDC hdc; 
    HBRUSH hBrush;
    RECT rect;
	int height = HIWORD(lParam);
	const WORD ID_TIMER = 1;
	GetClientRect(hwnd, &rect);
	int dx, dy;
	Shape* shape = NULL;
	BOOL gotUpdate = FALSE;
	
	if(message == circleUpdateMsg)
	{
		shape = &shapes[CIRCLE_N];
	}
		
	else if (message == triangleUpdateMsg)
	{
		shape = &shapes[TRIANGLE_N];
	}
	
	else if (message == squareUpdateMsg)
	{
		shape = &shapes[SQUARE_N];
	}

	if(shape != NULL)
	{
		dx = wParam - shape->origin.x;
		dy = lParam - shape->origin.y;
		
		hdc = GetDC(hwnd);
		shape->move(hdc, hwnd, shape, dx, dy);
		ReleaseDC(hwnd, hdc);
	}
	
	switch (message)
    {
		case WM_CREATE:	 
			createShapes(shapes);
			PostMessage(HWND_BROADCAST, updateRequestMsg, 0, 0);
			break;
			
	    case WM_PAINT:
			hdc = BeginPaint(hwnd, & ps);
			clear(&hdc, rect);
			drawShapes(&hdc, shapes);
			EndPaint(hwnd, & ps);
	   		break;
			
  		case WM_DESTROY:
            PostQuitMessage (0); /* send a WM_QUIT to the message queue */
            break;
            
        default:   
			/* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

