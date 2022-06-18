#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

int main() {
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);


    return 0;
}