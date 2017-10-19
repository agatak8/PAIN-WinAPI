#include "globals.h"

double scale = 0.75;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
	HDC hdc; 
    HBRUSH hBrush;
    RECT rect;
	int height = HIWORD(lParam);
	const WORD ID_TIMER = 1;
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
		SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx (hdc, 32767, 32767, NULL) ;
		SetViewportExtEx (hdc, scale*32767, scale*32767, NULL) ;
		shape->move(hdc, hwnd, shape, dx, dy);
		ReleaseDC(hwnd, hdc);
	}
	
	switch (message)
    {
		case WM_CREATE:	 
			createShapes(shapes);
			hdc = BeginPaint(hwnd, & ps);
			SetMapMode(hdc, MM_ISOTROPIC);
			SetWindowExtEx (hdc, 32767, 32767, NULL) ;
			SetViewportExtEx (hdc, scale*32767, scale*32767, NULL) ;
			GetClientRect(hwnd, &rect);
			DPtoLP(hdc, (PPOINT) &rect, 2);
			clear(&hdc, rect);
			EndPaint(hwnd, & ps);
			PostMessage(HWND_BROADCAST, updateRequestMsg, 0, 0);
			break;
			
	    case WM_PAINT:
			hdc = BeginPaint(hwnd, & ps);
			SetMapMode(hdc, MM_ISOTROPIC);
			SetWindowExtEx (hdc, 32767, 32767, NULL) ;
			SetViewportExtEx (hdc, scale*32767, scale*32767, NULL) ;
			GetClientRect(hwnd, &rect);
			DPtoLP(hdc, (PPOINT) &rect, 2);
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

