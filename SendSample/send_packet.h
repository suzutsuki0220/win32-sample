#ifndef __SEND_PACKET_H__
#define __SEND_PACKET_H__

void actionSoushinClicked(HWND hWnd);
int send_packet(PSTR host, const char *mes, char *resp, size_t res_size);

#endif  // __SEND_PACKET_H__
