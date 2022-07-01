#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_in serv_adr;
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_adr.sin_port = htons(9995);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    puts("connected");

    char buf[64];
    read(sock, buf, sizeof(buf));
    puts(buf);

    return 0;
}
