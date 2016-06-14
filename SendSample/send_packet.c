#include <tchar.h>
#include <winsock2.h>

#include "my_fieldid.h"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

// 「送信」ボタンがクリックされた時の動作
void
actionSoushinClicked(HWND hWnd)
{
    char response[8192];

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
        SetWindowText(GetDlgItem(hWnd, FIELD_ID_RESP), _T(response));
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