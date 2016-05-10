#include <windows.h>
#include <tchar.h>

// 定数
#define WINDOW_WIDTH (400) // ウィンドウの幅
#define WINDOW_HEIGHT (300) // ウィンドウの高さ
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - WINDOW_WIDTH ) / 2)
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - WINDOW_HEIGHT ) / 2)

// プロトタイプ宣言
HWND Create(HINSTANCE hInst);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


/**  Entry Point 
  *
  * 引数1: インスタンスハンドル
  * 引数2: 自分自身の別インスタンスの確認に使用されていた(Win16 の産物、Win32では常にNULL)
  * 引数3: コマンドラインから受け取った引数
  * 引数4: アプリケーションの初期表示方法
  *
 **/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
    HWND hWnd;
    MSG msg;

    // ウィンドウを作成する
    hWnd = Create( hInst );
    if( hWnd == NULL )
    {
        MessageBox( NULL, _T("ウィンドウの作成に失敗しました"), _T("エラー"), MB_OK );
        return 1;
    }

    // ウィンドウを表示する
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    // メッセージループ
    while( 1 )
    {
        BOOL ret = GetMessage( &msg, NULL, 0, 0 ); // メッセージを取得する
        if( ret == 0 || ret == -1 )
        {
            // アプリケーションを終了させるメッセージが来ていたら、
            // あるいは GetMessage() が失敗したら( -1 が返されたら ）、ループを抜ける
            break;
        }
        else
        {
            // メッセージを処理する
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    return 0;
}

// ウィンドウを作成する
HWND Create(HINSTANCE hInst)
{
    WNDCLASSEX wc;

    // ウィンドウクラスの情報を設定
    wc.cbSize = sizeof(wc); // 構造体サイズ
    wc.style = CS_HREDRAW | CS_VREDRAW; // スタイル
    wc.lpfnWndProc = WndProc; // ウィンドウプロシージャ
    wc.cbClsExtra = 0; // 拡張情報１
    wc.cbWndExtra = 0; // 拡張情報２
    wc.hInstance = hInst; // インスタンスハンドル
    wc.hIcon = (HICON)LoadImage( // アイコン
        NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
        0, 0, LR_DEFAULTSIZE | LR_SHARED
    );
    wc.hIconSm = wc.hIcon; // 子アイコン
    wc.hCursor = (HCURSOR)LoadImage( // マウスカーソル
        NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
        0, 0, LR_DEFAULTSIZE | LR_SHARED
    );
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ウィンドウ背景
    wc.lpszMenuName = NULL; // メニュー名
    wc.lpszClassName = _T("Default Class Name");// ウィンドウクラス名

    // ウィンドウクラスを登録する
    if( RegisterClassEx( &wc ) == 0 ){ return NULL; }

    // ウィンドウを作成する
    return CreateWindow(
        wc.lpszClassName, // ウィンドウクラス名
        _T("Sample Program"), // タイトルバーに表示する文字列
        WS_OVERLAPPEDWINDOW, // ウィンドウの種類
        WINDOW_X, // ウィンドウを表示する位置（X座標）
        WINDOW_Y, // ウィンドウを表示する位置（Y座標）
        WINDOW_WIDTH, // ウィンドウの幅
        WINDOW_HEIGHT, // ウィンドウの高さ
        NULL, // 親ウィンドウのウィンドウハンドル
        NULL, // メニューハンドル
        hInst, // インスタンスハンドル
        NULL // その他の作成データ
    );
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HMENU hMenu;
    int wmId;

    switch( msg )
    {
    case WM_CREATE: // ウィンドウが作られたとき
        // メニューリソースをロードする
        hMenu = LoadMenu( NULL, _T("WIN_MENU") );
        // ウィンドウにメニューリソースを割り当てる
        SetMenu( hWnd, hMenu );

        return 0;

    case WM_COMMAND:
        wmId= LOWORD(wp);
        switch (wmId){
        case 40006:
            DestroyWindow(hWnd);
            break;
        case 40013:
            MessageBox(NULL, "ver1.00", "バージョン情報", MB_OK);
            break;
        default: ;
        }
        break;

    case WM_CLOSE: // ウィンドウが閉じられるとき
        // ウィンドウからメニューバーを削除
        SetMenu( hWnd, NULL );
        // メニューバーリソースを破棄する
        DestroyMenu( hMenu );
        hMenu = NULL;

        break; // ウィンドウを閉じる処理はDefWindowProc()に任せる

    case WM_DESTROY: // ウィンドウが破棄されるとき
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wp, lp );
}
