#include <tchar.h>

#include "my_fieldid.h"
#include "MyWindow.h"

// �w�肵�����W�Ƀe�L�X�g���o�͂���
void
drawText(HWND hWnd, int x, int y, const char* message)
{
    HDC hdc;

    //�f�o�C�X�R���e�L�X�g�擾
    hdc = GetDC(hWnd);
    if (hdc) {
        //�`��
        TextOut(hdc, x, y, _T(message), strlen(message));
        //�K�����
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

// �E�B���h�E�T�C�Y�ɍ��킹�ē��͗��̃T�C�Y��ύX����
void
resizeReqBox(HWND hWnd)
{
    int xx, yy, box_height;
    RECT WndRect;
    GetClientRect(hWnd, &WndRect);

    const int top_area_height = 70;    // �u�ڑ���v�A�u���N�G�X�g�v�\���̈�̍���
    const int middle_area_height = 70; // �uContent�v�A�u���M�v�{�^���̕\���̈�̍���

    xx = WndRect.right;   // �E�B���h�E��
    yy = WndRect.bottom;  // �E�B���h�E����

    box_height = (yy - top_area_height - middle_area_height) / 2;
    if (box_height < 10) {
        box_height = 10;
    }

    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_REQ), 0, 0, top_area_height, xx, box_height, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_BTN_SOUSHIN), 0, xx/2-35, top_area_height+box_height+middle_area_height-35, 70, 30, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_CONTENT), 0, 80, top_area_height+box_height+5, xx-80, 30, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_RESP), 0, 0, top_area_height+box_height+middle_area_height, xx, box_height, SWP_NOACTIVATE | SWP_NOZORDER);

    drawText(hWnd, 0, 5, "�ڑ���");
    drawText(hWnd, 0, 40, "���N�G�X�g");
    drawText(hWnd, 0, 70+box_height+10, "Query");
}
