#include <WinSock2.h>
#include <fcntl.h>
#include <windows.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define BUFFER_SIZE 64

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s ip port\n", argv[0]);
        return 1;
    }

    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        puts("FUCK WINDOWS");
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("124.220.210.31");
    server_address.sin_port = htons(port);

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);  // TCP
    assert(sockfd > 0);

    int ret = connect(sockfd, (SOCKADDR*)&server_address,
                      sizeof(server_address));
    assert(ret != SOCKET_ERROR);

    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];

    while (1) {
        printf("Enter message:\n");
        scanf("%s", send_buf);
        // puts("DONE");
        int len = strlen(send_buf);
        send_buf[len] = ' ';
        len++;
        send_buf[len] = '\0';
        send(sockfd, send_buf, len, 0);

        if (fds[1].revents & POLLRDHUP) {
            printf("server closed the connection.\n");
            break;
        } else if (fds[1].revents & POLLIN) {
            // receving data
            memset(read_buf, 0, BUFFER_SIZE);
            recv(fds[1].fd, read_buf, BUFFER_SIZE - 1, 0);
            printf("rec: %s",  read_buf);
        }

        memset(read_buf, 0, BUFFER_SIZE);
        recv(sockfd, read_buf, 10, 0);
        printf("Rec: \"%s\"\n", read_buf);
    }

    closesocket(sockfd);

    WSACleanup();

    return 0;
}
