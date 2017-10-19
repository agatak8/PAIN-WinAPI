#pragma once
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "Gdi32.lib")
#include <windows.h>
#include "shapes.h"

#define SQUARE_SIDE_CM 2
#define TRIANGLE_SIDE_CM 4
#define CIRCLE_RADIUS_CM 6
#define SQUARE_COLOR RGB(255,255,0)
#define TRIANGLE_COLOR RGB(255,0,255)
#define CIRCLE_COLOR RGB(0,255,255)

#define PAIN_WIDTH 640
#define PAIN_HEIGHT 480
#define BG_COLOR RGB(10,20,30)

#define CIRCLE_N 0
#define TRIANGLE_N 1
#define SQUARE_N 2

#define MOVE_SPEED 5

extern int currentShapeN;
extern Shape shapes[3];

extern int circleUpdateMsg;
extern int triangleUpdateMsg;
extern int squareUpdateMsg;

extern int updateRequestMsg;


