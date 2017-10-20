#include "globals.h"

#define SETMAPMODE() {\
	GetClientRect(hwnd, &rect);\
	SetViewportOrgEx(hdc, rect.right/2, rect.bottom/2, NULL);\
	SetMapMode(hdc, MM_ISOTROPIC);\
	SetWindowExtEx(hdc, 32767, -32767, NULL);\
	SetViewportExtEx(hdc, scale*32767, scale*32767, NULL);\
	}

double scale = 0.5;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
	HDC hdc; 
    HBRUSH hBrush;
    RECT rect;
	int dx, dy;
	Shape* shape = NULL;
	
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
		SETMAPMODE();
		shape->move(hdc, hwnd, shape, dx, dy);
		ReleaseDC(hwnd, hdc);
	}
	
	switch (message)
    {
		case WM_CREATE:	 
			hdc = BeginPaint(hwnd, & ps);
			SETMAPMODE();
			createShapes(hdc, shapes);
			DPtoLP(hdc, (PPOINT) &rect, 2);
			clear(&hdc, rect);
			EndPaint(hwnd, & ps);
			PostMessage(HWND_BROADCAST, updateRequestMsg, 0, 0);
			break;
			
	    case WM_PAINT:
			hdc = BeginPaint(hwnd, & ps);
			SETMAPMODE();
			DPtoLP(hdc, (PPOINT) &rect, 2);
			clear(&hdc, rect);
			drawShapes(&hdc, shapes);
			EndPaint(hwnd, & ps);
	   		break;
	   		
	   	case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_OEM_PLUS:
					if(GetKeyState(VK_CONTROL) & 0x8000 && scale <= 50*SCALE_SPEED)
					{
						scale += SCALE_SPEED;
						InvalidateRect(hwnd, NULL, FALSE);
					}
					break;
				case VK_OEM_MINUS:
					if(GetKeyState(VK_CONTROL) & 0x8000 && scale >= 2*SCALE_SPEED)
					{
						scale -= SCALE_SPEED;
						InvalidateRect(hwnd, NULL, FALSE);
					}
					break;
			}
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

