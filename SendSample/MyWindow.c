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
        TextOut(hdc, x, y, _T(message), strlen(message));
        //必ず解放
        ReleaseDC(hWnd, hdc);
    }
}

void
drawText2(HWND hWnd, int x, int y, const char* message)
{
    HDC hdc;
    HFONT hFont;
    PAINTSTRUCT ps;

    hdc = BeginPaint(hWnd, &ps);
    hFont = CreateFont(
			40, 0, 0, 0, FW_BOLD, TRUE, TRUE, FALSE,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			VARIABLE_PITCH | FF_ROMAN, NULL);
    SelectObject(hdc, hFont);
    TextOut(hdc, x, y, _T(message), strlen(message));
    SelectObject(hdc , GetStockObject(SYSTEM_FONT));

    DeleteObject(hFont);
    EndPaint(hWnd, &ps);
}

// ウィンドウサイズに合わせて入力欄のサイズを変更する
void
resizeReqBox(HWND hWnd)
{
    int xx, yy, box_height;
    RECT WndRect;
    GetClientRect(hWnd, &WndRect);

    const int top_area_height = 70;    // 「接続先」、「リクエスト」表示領域の高さ
    const int middle_area_height = 70; // 「Content」、「送信」ボタンの表示領域の高さ

    xx = WndRect.right;   // ウィンドウ幅
    yy = WndRect.bottom;  // ウィンドウ高さ

    box_height = (yy - top_area_height - middle_area_height) / 2;
    if (box_height < 10) {
        box_height = 10;
    }

    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_REQ), 0, 0, top_area_height, xx, box_height, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_BTN_SOUSHIN), 0, xx/2-35, top_area_height+box_height+middle_area_height-35, 70, 30, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_CONTENT), 0, 80, top_area_height+box_height+5, xx-80, 30, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_RESP), 0, 0, top_area_height+box_height+middle_area_height, xx, box_height, SWP_NOACTIVATE | SWP_NOZORDER);

    drawText(hWnd, 0, 5, "接続先");
    drawText(hWnd, 0, 40, "リクエスト");
    drawText(hWnd, 0, 70+box_height+10, "Query");
}
