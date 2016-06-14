#ifndef __MY_WINDOW_H__
#define __MY_WINDOW_H__

#include <windows.h>

void drawText(HWND hWnd, int x, int y, const char* message);
void drawText2(HWND hWnd, int x, int y, const char* message);
void resizeReqBox(HWND hwnd);

#endif  // __MY_WINDOW_H__
