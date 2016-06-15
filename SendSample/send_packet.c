#include <tchar.h>
#include <winsock2.h>
//#include <iconv.h>
#include <stdio.h>

#include "my_fieldid.h"
#include "send_packet.h"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

// 「送信」ボタンがクリックされた時の動作
void
actionSoushinClicked(HWND hWnd)
{
    char response[8192];
#if 0 // iconvはmingwでは使えなかった
    char convert_out[8192];
    size_t response_size = sizeof(response);
    size_t convert_out_size = sizeof(convert_out);
#endif

    size_t strHostLen = GetWindowTextLength(GetDlgItem(hWnd, FIELD_ID_HOST)) + 2;
    LPSTR  strHost    = malloc(strHostLen);
    size_t strReqLen  = GetWindowTextLength(GetDlgItem(hWnd, FIELD_ID_REQ)) + 2;
    LPSTR  strReq     = malloc(strReqLen);

    if (strHost && strReq) {
        GetWindowText(GetDlgItem(hWnd, FIELD_ID_HOST), strHost, strHostLen);
        GetWindowText(GetDlgItem(hWnd, FIELD_ID_REQ), strReq, strReqLen);
        memset(response, '\0', sizeof(response));
        send_packet(strHost, (char*)strReq, response, sizeof(response));
        //MessageBoxA(NULL, strHost, _T("result"), MB_OK);  // マルチバイト文字を受けるMessageBoxA
        
#if 0
        char *ptr_in = response;
        iconv_t ic;
        ic = iconv_open("SJIS", "UTF-8");
        iconv(ic, response, &response_size, convert_out, &convert_out_size);
        iconv_close(ic);
#endif

        // Win-APIを使って文字コードを変換する　(UTF-8→ShiftJIS)
        // UTF-8 to WideChar
        int lengthUnicode = MultiByteToWideChar(CP_UTF8, 0, response, strlen(response) + 1, NULL, 0);
        wchar_t bufUnicode[lengthUnicode+1];
        MultiByteToWideChar(CP_UTF8, 0, response, strlen(response) + 1, bufUnicode, lengthUnicode);
        // WideChar to ShiftJIS
        int lengthSjis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
        char bufSjis[lengthSjis];
        WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lengthUnicode + 1, bufSjis, lengthSjis, NULL, NULL);

        //SetWindowText(GetDlgItem(hWnd, FIELD_ID_RESP), _T(response));
        SetWindowText(GetDlgItem(hWnd, FIELD_ID_RESP), _T(bufSjis));
        free(strHost);
        strHost = NULL;
    }
}

int
send_packet(PSTR host, const char *mes, char *resp, size_t res_size)
{
    int ret = -1;
    int len = 0;
    int err = 0;
    WSADATA wsaData;
    SOCKET sock = -1;
    struct sockaddr_in client;

    err = WSAStartup(MAKEWORD(2,0), &wsaData);
    if (err != 0) {
        goto end;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // ERROR
        goto end;
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(80);
    client.sin_addr.S_un.S_addr = inet_addr((char*)host);

    if (connect(sock, (struct sockaddr *)&client, sizeof(client)) != 0) {
        // ERROR
        goto end;
    }

    len = send(sock, mes, strlen(mes), MSG_NOSIGNAL);
    if (len < 0) {
        // ERROR
        goto end;
    }
    
    len = recv(sock, resp, res_size-1, MSG_NOSIGNAL);
    resp[len] = '\0';

    ret = 0;

end:
    WSACleanup();

    return ret;
}