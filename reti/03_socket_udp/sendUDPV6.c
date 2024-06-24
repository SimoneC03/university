#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in6 remote_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    int received_bytes = 0;
    char sendline[1000];
    char recline[1000];
    char ipv6_addr[INET6_ADDRSTRLEN];

    if(argc != 3) {
        printf("Error. Please insert IP and Port\n");
        return -1;
    }

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error occurred while socket opening\n");
        return -1;
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &(remote_addr.sin6_addr));
    remote_addr.sin6_port = htons(atoi(argv[2]));

    while(fgets(sendline, 1000, stdin) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
        received_bytes = recvfrom(sockfd, recline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        inet_ntop(AF_INET6, &(remote_addr.sin6_addr), ipv6_addr, INET6_ADDRSTRLEN);
        printf("IP = %s, P = %d, msg = %s\n", ipv6_addr, ntohs(remote_addr.sin6_port), recline);
        if(strcmp(recline, "end\n") == 0) break;
    }

    printf("End of communication\n");
    close(sockfd);
}