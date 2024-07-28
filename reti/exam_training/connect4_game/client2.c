#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1000

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in remote_addr;
    char sendline[MAX_BUFFER_SIZE];
    char recline[MAX_BUFFER_SIZE];
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

    sendto(sockfd, "Client2", 8, 0, (struct sockaddr *)&remote_addr, len);

    printf("The game will start soon...\n");

    // game start alert
    memset(recline, 0, MAX_BUFFER_SIZE);
    received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
    recline[received_bytes] = 0;
    printf("%s", recline);

    printf("Wait for your turn...\n");
    
    for(;;) {
        memset(recline, 0, MAX_BUFFER_SIZE);
        received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        printf("%s", recline);
        memset(sendline, 0, MAX_BUFFER_SIZE);
        send_col:
        fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
        memset(recline, 0, MAX_BUFFER_SIZE);
        received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        printf("%s", recline);
        if(strstr(recline, "not valid") != NULL) {
            goto send_col;
        }
        printf("Wait for your turn...\n");
    }

    printf("End of communication\n");
    close(sockfd);

    return 0;
}