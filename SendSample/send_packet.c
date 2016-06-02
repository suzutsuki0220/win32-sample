#include <winsock2.h>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

int send_packet(PSTR host, const char *mes, char *resp, size_t res_size)
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