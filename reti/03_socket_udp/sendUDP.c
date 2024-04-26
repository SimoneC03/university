#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in remote_addr;
    char sendline[1000];
    char recline[1000];
    socklen_t len = sizeof(struct sockaddr_in);
    int received_bytes = 0;
    
    if(argc != 3) {
        printf("Error. Please insert IP and port\n");
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error occurred while opening socket\n");
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
    remote_addr.sin_port = htons(atoi(argv[2]));

    while(fgets(sendline, 1000, stdin) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
        received_bytes = recvfrom(sockfd, recline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        printf("IP = %s, P = %d, msg = %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), recline);
        if(strcmp(recline, "end\n") == 0) break;
    }

    printf("End of communication\n");
    close(sockfd);

    return 0;
}