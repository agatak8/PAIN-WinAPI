#pragma once
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "Gdi32.lib")
#define UNICODE
#include <windows.h>

typedef struct ShapeStruct
{
	RECT rect; //bounding rectangle
	POINT origin;
	COLORREF color;
	UINT rectSide;
	void (*draw) (HDC*, struct ShapeStruct*);
	void (*move) (HDC, HWND, struct ShapeStruct*, int, int);
} Shape, Circle, Square, Triangle;

Circle createCircle(POINT, COLORREF, UINT);
Triangle createTriangle(POINT, COLORREF, UINT);
Square createSquare(POINT, COLORREF, UINT);
int cmToPixels(double cm);
RECT getShapeRect(Shape*);
void drawShapes(HDC* hdc, Shape* shapes);
void clear(HDC* hdc, RECT rect);
void createShapes(HDC hdc, Shape* shapesBuf);
