#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in6 dest_addr;
    char sendline[1000];
    char recvline[1000];

    if(argc < 3) {
        printf("Please insert IP address and port\n");
        return -1;
    }

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
        printf("Error occurred while socket opening\n");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &dest_addr.sin6_addr);
    // or
    // dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
    dest_addr.sin6_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    while(fgets(sendline, 999, stdin) != NULL) {
        send(sockfd, sendline, strlen(sendline), 0);
        received_bytes = recv(sockfd, recvline, 999, 0);
        recvline[received_bytes] = 0;
        printf("msg = %s\n", recvline);

        if(strcmp(recvline, "end\n") == 0) {
            printf("End of communication\n");
            break;
        }
    }

    close(sockfd);

    return 0;
}