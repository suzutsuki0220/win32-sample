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
        TextOut(hdc,x, y, _T(message), strlen(message));
        //�K�����
        ReleaseDC(hWnd, hdc);
    }
}

// �E�B���h�E�T�C�Y�ɍ��킹�ē��͗��̃T�C�Y��ύX����
void
resizeReqBox(HWND hWnd)
{
    int xx, yy;
    RECT WndRect;
    GetClientRect(hWnd, &WndRect);

    xx = WndRect.right;   // �E�B���h�E��
    yy = WndRect.bottom;  // �E�B���h�E����
    
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_REQ), 0, 0, 100, xx, 200, SWP_NOACTIVATE | SWP_NOZORDER);
    SetWindowPos(GetDlgItem(hWnd, FIELD_ID_RESP), 0, 0, 400, xx, 200, SWP_NOACTIVATE | SWP_NOZORDER);
}
