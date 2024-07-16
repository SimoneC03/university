#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_MESSAGE_TEXT 200

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

    sendto(sockfd, "Connected\n", 50, 0, (struct sockaddr *)&remote_addr, len);
    for(;;) {
        received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        printf("%s", recline);
        // send selected action
        fgets(sendline, MAX_BUFFER_SIZE, stdin);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
        // end communication
        if(sendline[0] == 'q') break;
        else if(sendline[0] == '0') {
            printf("Insert the text of the new message to send:\n");
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_MESSAGE_TEXT, stdin);
            sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
            received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            recline[received_bytes] = 0;
            printf("%s", recline);
        } else if(sendline[0] == '1') {
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            recline[received_bytes] = 0;
            printf("%s", recline);
        } else if(sendline[0] == '2') {
            printf("Insert the index of the message to edit: ");
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_MESSAGE_TEXT, stdin);
            sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
            printf("Insert the new text for the message with index %d:", atoi(sendline));
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_MESSAGE_TEXT, stdin);
            sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
            received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            recline[received_bytes] = 0;
            printf("%s", recline);
        } else if(sendline[0] == '3') {
            printf("Insert the index of the message to delete: ");
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_MESSAGE_TEXT, stdin);
            sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
            received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            recline[received_bytes] = 0;
            printf("%s", recline);
        }
    }

    printf("End of communication\n");
    close(sockfd);

    return 0;
}