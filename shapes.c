#include <windows.h>
#include "shapes.h"
#include "globals.h"

void moveShape(HDC, HWND, Shape*, int, int);
void drawCircle(HDC*, Shape*);
void drawTriangle(HDC*, Shape*);
void drawSquare(HDC*, Shape*);

int randint(int min, int max)
{
	return (rand()%(max + 1) + min);
}

void moveShape(HDC hdc, HWND hwnd, Shape* shape, int dx, int dy)
{
	RECT shapeRect = getShapeRect(shape);
	shape->origin.x += dx;
	shape->origin.y += dy;
	shape->draw(&hdc, shape);	
	
	// refresh old shape area
	LPtoDP(hdc, (PPOINT)&shapeRect, 2);
	shapeRect.right +=1;
	shapeRect.bottom +=1;
	InvalidateRect(hwnd, &shapeRect, FALSE);
	// refresh new shape area
	shapeRect = getShapeRect(shape);
	LPtoDP(hdc, (PPOINT)&shapeRect, 2);
	shapeRect.right +=1;
	shapeRect.bottom +=1;
	InvalidateRect(hwnd, &shapeRect, FALSE);
}

void setShape(Shape* shape, POINT origin, COLORREF color, UINT rectSide)
{
	shape->origin = origin;
	shape->color = color;
	shape->rectSide = rectSide;
	shape->move = &moveShape;
}

RECT getShapeRect(Shape* shape)
{
	RECT rect;
	rect.left = shape->origin.x - (shape->rectSide)/2;
	rect.top = shape->origin.y + (shape->rectSide)/2;
	rect.right = shape->origin.x + (shape->rectSide)/2;
	rect.bottom = shape->origin.y - (shape->rectSide)/2;
	return rect;
}

Circle createCircle(POINT origin, COLORREF color, UINT radius)
{
	Circle circle;
	
	setShape(&circle, origin, color, 2*radius);
	circle.draw = &drawCircle;
	
	return circle;
}

Triangle createTriangle(POINT origin, COLORREF color, UINT side)
{
	Triangle triangle;
	
	setShape(&triangle, origin, color, side);
	triangle.draw = &drawTriangle;
	
	return triangle;
}

Square createSquare(POINT origin, COLORREF color, UINT side)
{
	Square square;
	
	setShape(&square, origin, color, side);
	square.draw = &drawSquare;
	
	return square;
}


void drawCircle(HDC* hdc, Shape* shape)
{
	HPEN hPen = CreatePen(PS_SOLID,1,shape->color);
	HBRUSH hBrush = CreateSolidBrush(shape->color);
	RECT rect = getShapeRect(shape);
	
 	SelectObject(*hdc,hPen);
 	SelectObject(*hdc,hBrush);
 	
	Ellipse(*hdc, rect.left, rect.top, rect.right, rect.bottom);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void drawTriangle(HDC* hdc, Shape* shape)
{
	POINT points[3];
	HPEN hPen = CreatePen(PS_SOLID,1,shape->color);
	HBRUSH hBrush = CreateSolidBrush(shape->color);
	RECT rect = getShapeRect(shape);
	
 	SelectObject(*hdc,hPen);
 	SelectObject(*hdc,hBrush);
 	
 	points[0].x = shape->origin.x;
	points[0].y = rect.top;
	points[1].x = rect.left;
	points[1].y = rect.bottom;
	points[2].x = rect.right;
	points[2].y = rect.bottom;

	Polygon(*hdc, points, 3);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void drawSquare(HDC* hdc, Shape* shape)
{
	HPEN hPen = CreatePen(PS_SOLID,1,shape->color);
	HBRUSH hBrush = CreateSolidBrush(shape->color);
	RECT rect = getShapeRect(shape);
	
 	SelectObject(*hdc,hPen);
 	SelectObject(*hdc,hBrush);
 	
	Rectangle(*hdc, rect.left, rect.top, rect.right, rect.bottom);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);
}


void drawShapes(HDC* hdc, Shape* shapes)
{	
	for(int i = 0; i < 3; ++i)
	{
		shapes[i].draw(hdc, &shapes[i]);
	}
}

void clear(HDC* hdc, RECT rect)
{
	HPEN hPen = CreatePen(PS_SOLID,1,BG_COLOR);
	HBRUSH hBrush = CreateSolidBrush(BG_COLOR);
	
 	SelectObject(*hdc,hPen);
 	SelectObject(*hdc,hBrush);
 	
	Rectangle(*hdc, rect.left, rect.top, rect.right, rect.bottom);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void createShapes(HDC hdc, Shape* shapesBuf)
{
	POINT origins[3];
	for(int i = 0; i < 3; ++i)
	{
		origins[i].x = randint(0, PAIN_WIDTH);
		origins[i].y = randint(0, PAIN_HEIGHT);
	}
	DPtoLP(hdc, origins, 3);
	shapesBuf[CIRCLE_N] = createCircle(origins[CIRCLE_N], CIRCLE_COLOR, CIRCLE_RADIUS_CM*100);
	shapesBuf[TRIANGLE_N] = createTriangle(origins[TRIANGLE_N], TRIANGLE_COLOR, TRIANGLE_SIDE_CM*100);
	shapesBuf[SQUARE_N] = createSquare(origins[SQUARE_N], SQUARE_COLOR, SQUARE_SIDE_CM*100);	
}

