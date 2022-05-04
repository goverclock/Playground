#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
#include <cstdlib>
#include <sys/socket.h>
#include <cassert>
#include <iostream>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: %s ip port\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);
    
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd > 0);
    int ret = connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    assert(ret >= 0);

    const char *msg = "hello";
    send(sockfd, msg, strlen(msg), 0);
    close(sockfd);

    return 0;
}
