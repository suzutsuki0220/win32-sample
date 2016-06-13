#include <windows.h>
#include <tchar.h>

#include "my_fieldid.h"
#include "send_packet.h"
#include "MyWindow.h"

// �萔
#define WINDOW_WIDTH (500) // �E�B���h�E�̕�
#define WINDOW_HEIGHT (600) // �E�B���h�E�̍���
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - WINDOW_WIDTH ) / 2)
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - WINDOW_HEIGHT ) / 2)

// �v���g�^�C�v�錾
HWND Create(HINSTANCE hInst);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


/**  WinMain: Entry Point **
  *
  * ����1: �C���X�^���X�n���h��
  * ����2: �������g�̕ʃC���X�^���X�̊m�F�Ɏg�p����Ă���(Win16 �̎Y���AWin32�ł͏��NULL)
  * ����3: �R�}���h���C������󂯎��������
  * ����4: �A�v���P�[�V�����̏����\�����@
  *
 **/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
    HWND hWnd;
    MSG msg;

    // �E�B���h�E���쐬����
    hWnd = Create( hInst );
    if (hWnd == NULL)
    {
        MessageBox(NULL, _T("�E�B���h�E�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK);
        return 1;
    }

    // �{�^��
    HWND hwnd_button = CreateWindow("button","���M",WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 50,50,70,30,hWnd,(HMENU)10000,hInst,NULL);
    if (hwnd_button == NULL)
    {
        MessageBox(NULL, _T("�E�B���h�E�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK);
        return 1;
    }

    // �ڑ�����͗� (EDIT)
    CreateWindow(
        _T("EDIT"), _T("192.168.32.72"), 
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        0, 0, 200, 30, hWnd, (HMENU)FIELD_ID_HOST,
        hInst, NULL
    );

    // ���N�G�X�g���͗� (EDIT)
    CreateWindow(
        _T("EDIT"), _T("HEAD / HTTP1.0\r\n\r\n"), 
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
        0, 100, 400, 200, hWnd, (HMENU)FIELD_ID_REQ,
        hInst, NULL
    );
    // ���X�|���X�\���� (EDIT)
    CreateWindow(
        _T("EDIT"), _T(""), 
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
        0, 400, 400, 200, hWnd, (HMENU)FIELD_ID_RESP,
        hInst, NULL
    );

    // �E�B���h�E��\������
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // ���b�Z�[�W���[�v
    while( 1 )
    {
        BOOL ret = GetMessage( &msg, NULL, 0, 0 ); // ���b�Z�[�W���擾����
        if( ret == 0 || ret == -1 )
        {
            // �A�v���P�[�V�������I�������郁�b�Z�[�W�����Ă�����A
            // ���邢�� GetMessage() �����s������( -1 ���Ԃ��ꂽ�� �j�A���[�v�𔲂���
            break;
        }
        else
        {
            // ���b�Z�[�W����������
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    return 0;
}

// �E�B���h�E���쐬����
HWND Create(HINSTANCE hInst)
{
    WNDCLASSEX wc;

    // �E�B���h�E�N���X�̏���ݒ�
    wc.cbSize = sizeof(wc); // �\���̃T�C�Y
    wc.style = CS_HREDRAW | CS_VREDRAW; // �X�^�C��
    wc.lpfnWndProc = WndProc; // �E�B���h�E�v���V�[�W��
    wc.cbClsExtra = 0; // �g�����P
    wc.cbWndExtra = 0; // �g�����Q
    wc.hInstance = hInst; // �C���X�^���X�n���h��
    wc.hIcon = (HICON)LoadImage( // �A�C�R��
        NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED
    );
    wc.hIconSm = wc.hIcon; // �q�A�C�R��
    wc.hCursor = (HCURSOR)LoadImage( // �}�E�X�J�[�\��
        NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
        0, 0, LR_DEFAULTSIZE | LR_SHARED
    );
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �E�B���h�E�w�i
    wc.lpszMenuName = NULL; // ���j���[��
    wc.lpszClassName = _T("Default Class Name");// �E�B���h�E�N���X��

    // �E�B���h�E�N���X��o�^����
    if( RegisterClassEx( &wc ) == 0 ){ return NULL; }

    // �E�B���h�E���쐬����
    return CreateWindow(
        wc.lpszClassName, // �E�B���h�E�N���X��
        _T("Sample Program"), // �^�C�g���o�[�ɕ\�����镶����
        WS_OVERLAPPEDWINDOW, // �E�B���h�E�̎��
        WINDOW_X, // �E�B���h�E��\������ʒu�iX���W�j
        WINDOW_Y, // �E�B���h�E��\������ʒu�iY���W�j
        WINDOW_WIDTH, // �E�B���h�E�̕�
        WINDOW_HEIGHT, // �E�B���h�E�̍���
        NULL, // �e�E�B���h�E�̃E�B���h�E�n���h��
        NULL, // ���j���[�n���h��
        hInst, // �C���X�^���X�n���h��
        NULL // ���̑��̍쐬�f�[�^
    );
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HMENU hMenu;
    int wmId;

    char response[1024];

    LPSTR strHost = NULL;
    size_t strHostLen = 0;
    LPSTR strReq = NULL;
    size_t strReqLen = 0;

    switch( msg )
    {
    case WM_CREATE: // �E�B���h�E�����ꂽ�Ƃ�
        // ���j���[���\�[�X�����[�h����
        hMenu = LoadMenu(NULL, _T("WIN_MENU"));
        // �E�B���h�E�Ƀ��j���[���\�[�X�����蓖�Ă�
        SetMenu(hWnd, hMenu);

        return 0;
    case WM_KEYDOWN:
        drawText(hWnd, 0, 0, "������\��");
        return 0;
    case WM_COMMAND:
        wmId= LOWORD(wp);
        switch (wmId){
        case 40006:
            DestroyWindow(hWnd);
            break;
        case 10000:
            // �{�^������
            strHostLen = GetWindowTextLength(GetDlgItem(hWnd, FIELD_ID_HOST)) + 2;
            strHost = malloc(strHostLen);
            strReqLen = GetWindowTextLength(GetDlgItem(hWnd, FIELD_ID_REQ)) + 2;
            strReq = malloc(strReqLen);
            if (strHost && strReq) {
                GetWindowText(GetDlgItem(hWnd, FIELD_ID_HOST), strHost, strHostLen);
                GetWindowText(GetDlgItem(hWnd, FIELD_ID_REQ), strReq, strReqLen);
                memset(response, '\0', sizeof(response));
                send_packet(strHost, (char*)strReq, response, sizeof(response));
                //MessageBoxA(NULL, strHost, _T("result"), MB_OK);  // �}���`�o�C�g�������󂯂�MessageBoxA
                SetWindowText(GetDlgItem(hWnd, FIELD_ID_RESP), _T(response));
                free(strHost);
                strHost = NULL;
            }
            return 0;
        case 40013:
            MessageBox(NULL, "ver1.00", "�o�[�W�������", MB_OK);
            break;
        default:
             break;
        }
        break;

    case WM_PAINT:
        drawText(hWnd, 0, 55, "�ڑ���");
        drawText(hWnd, 0, 70, "���N�G�X�g");

        // ���N�G�X�g���͗��̃T�C�Y�ύX
        resizeReqBox(hWnd);

        break;

    case WM_CLOSE: // �E�B���h�E��������Ƃ�
        // �E�B���h�E���烁�j���[�o�[���폜
        SetMenu( hWnd, NULL );
        // ���j���[�o�[���\�[�X��j������
        DestroyMenu( hMenu );
        hMenu = NULL;

        break; // �E�B���h�E����鏈����DefWindowProc()�ɔC����

    case WM_DESTROY: // �E�B���h�E���j�������Ƃ�
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wp, lp );  // �����ŏ������Ȃ����b�Z�[�W���V�X�e���ɓn��
}
