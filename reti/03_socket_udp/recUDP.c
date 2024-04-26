#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char msg[1000];
    int received_bytes = 0;

    if(argc != 2) {
        printf("Error. Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0) < 0)) {
        printf("Error occurred while opening socket\n");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
        printf("Error. Please insert a different port number\n");
        return -1;
    }

    for(;;) {
        received_bytes = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&remote_addr, &len);
        msg[received_bytes] = 0;

        sendto(sockfd, msg, received_bytes, 0, (struct sockaddr *)&remote_addr, len);

        printf("IP = %s, P = %d, msg = %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), msg);
        if(strcmp(msg, "end\n") == 0) {
            break;
        }
    }

    printf("End of comnunication\n");
    close(sockfd);

    return 0;
}