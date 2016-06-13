#include <tchar.h>

#include "my_fieldid.h"
#include "MyWindow.h"

// 指定した座標にテキストを出力する
void
drawText(HWND hWnd, int x, int y, const char* message)
{
    HDC hdc;

    //デバイスコンテキスト取得
    hdc = GetDC(hWnd);
    if (hdc) {
        //描画
        TextOut(hdc,x, y, _T(message), strlen(message));
        //必ず解放
        ReleaseDC(hWnd, hdc);
    }
}

// ウィンドウサイズに合わせて入力欄のサイズを変更する
void
resizeReqBox(HWND hWnd)
{
    int xx, yy;
    RECT WndRect;
    GetClientRect(hWnd, &WndRect);

    xx = WndRect.right;   // ウィンドウ幅
    yy = WndRect.bottom;  // ウィンドウ高さ
    
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_REQ), 0, 0, 100, xx, 200, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_RESP), 0, 0, 400, xx, 200, SWP_NOACTIVATE | SWP_NOZORDER);
}
