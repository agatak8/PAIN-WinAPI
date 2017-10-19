#pragma once
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "Gdi32.lib")
#define UNICODE
#include <windows.h>

extern LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
