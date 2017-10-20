#include "globals.h"

#define SETMAPMODE() {\
	GetClientRect(hwnd, &rect);\
	SetViewportOrgEx(hdc, rect.right/2, rect.bottom/2, NULL);\
	SetMapMode(hdc, MM_LOMETRIC);\
	}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
	HDC hdc; 
    HBRUSH hBrush;
    RECT rect;
	Shape* currentShape;
	int shapeUpdateMsg;
	int dx = 0, dy = 0;
	POINT mouse;
	
	if (message == updateRequestMsg)
	{
		PostMessage(HWND_BROADCAST, circleUpdateMsg, shapes[CIRCLE_N].origin.x, shapes[CIRCLE_N].origin.y);
		PostMessage(HWND_BROADCAST, triangleUpdateMsg, shapes[TRIANGLE_N].origin.x, shapes[TRIANGLE_N].origin.y);
		PostMessage(HWND_BROADCAST, squareUpdateMsg, shapes[SQUARE_N].origin.x, shapes[SQUARE_N].origin.y);
	}
	
	switch (message) /* handle the messages */
	    {
		case WM_CREATE:
			hdc = BeginPaint(hwnd, & ps);
			SETMAPMODE();
			DPtoLP(hdc, (PPOINT) &rect, 2);
			clear(&hdc, rect);
			createShapes(hdc, shapes);
			EndPaint(hwnd, &ps);
			
	    case WM_PAINT:
			hdc = BeginPaint(hwnd, & ps);
			SETMAPMODE();
			DPtoLP(hdc, (PPOINT) &rect, 2);
			clear(&hdc, rect);
			drawShapes(&hdc, shapes);
			EndPaint(hwnd, & ps);
	   		break;
	   		
	   	case WM_KEYDOWN:
			switch (wParam) 
			{
				case VK_LEFT:
					 dx = -MOVE_SPEED;
					 dy = 0;
					 break;
				case VK_RIGHT:
					 dx = MOVE_SPEED;
					 dy = 0; 
					 break;
				case VK_UP:
					 dx = 0;
					 dy = MOVE_SPEED;
					 break;
				case VK_DOWN:
					 dx = 0;
					 dy = -MOVE_SPEED;
					 break;
			}
			break;
			
		case WM_CHAR:
			switch (wParam)
			{
				case L'1':
					currentShapeN = CIRCLE_N;
					break;
				case L'2':
					currentShapeN = TRIANGLE_N;
					break;
				case L'3':
					currentShapeN = SQUARE_N;
					break;
			}
			break;
			
		case WM_LBUTTONDOWN:
			currentShape = &shapes[currentShapeN];
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			hdc = GetDC(hwnd);
			SETMAPMODE();
			DPtoLP(hdc, &mouse, 1);
			ReleaseDC(hwnd, hdc);
			
			dx = mouse.x - (currentShape->origin.x);
			dy = mouse.y - (currentShape->origin.y);
			break;
			
  		case WM_DESTROY:
            PostQuitMessage (0); /* send a WM_QUIT to the message queue */
            break;
            
        default:   
			/* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    
    if(dx != 0 || dy != 0)
	{
		currentShape = &shapes[currentShapeN];
		hdc = GetDC(hwnd);
		SETMAPMODE();
		currentShape->move(hdc, hwnd, currentShape, dx, dy);
		ReleaseDC(hwnd, hdc);
		switch(currentShapeN)
		{
			case CIRCLE_N:
				shapeUpdateMsg = circleUpdateMsg;
				break;
			case TRIANGLE_N:
				shapeUpdateMsg = triangleUpdateMsg;
				break;
			case SQUARE_N:
				shapeUpdateMsg = squareUpdateMsg;
				break;
		}
		PostMessage(HWND_BROADCAST, shapeUpdateMsg, currentShape->origin.x, currentShape->origin.y);
	}

    return 0;
}
