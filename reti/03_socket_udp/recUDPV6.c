#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in6 local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    char ipv6_addr[INET6_ADDRSTRLEN];
    char msg[1000];

    if(argc != 2) {
        printf("Error. Please insert port number\n");
        return -1;
    }

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error while opening socket\n");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin6_family = AF_INET6;
    local_addr.sin6_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
        printf("Error while binding socket\n");
        return -1;
    }

    for(;;) {
        received_bytes = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&remote_addr, &len);
        msg[received_bytes] = 0;

        sendto(sockfd, msg, received_bytes, 0, (struct sockaddr *)&remote_addr, len);

        inet_ntop(AF_INET6, &(remote_addr.sin6_addr), ipv6_addr, INET6_ADDRSTRLEN);

        printf("IP = %s, P = %d, msg = %s\n", ipv6_addr, ntohs(remote_addr.sin6_port), msg);
        if(strcmp(msg, "end\n") == 0) {
            break;
        }
    }


    return 0;
}