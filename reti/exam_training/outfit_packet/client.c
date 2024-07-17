#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1000

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in dest_addr;
    char sendline[1000];
    char recvline[1000];

    if(argc < 3) {
        printf("Please insert IP address and port\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error occurred while socket opening\n");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &dest_addr.sin_addr);
    dest_addr.sin_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    for(;;) {
        printf("0 - See all the available clothes\n1 - Buy one or more articles\n2 - Return an article\n(END) to end the operation\n");
        char *res = fgets(sendline, MAX_BUFFER_SIZE, stdin);
        send(sockfd, sendline, strlen(sendline), 0);
        if(strcmp(sendline, "END\n") == 0) {
            printf("End of communication\n");
            break;
        } else if(sendline[0] == '0') {
            memset(recvline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recvline, MAX_BUFFER_SIZE, 0);
            recvline[received_bytes] = 0;
            printf("%s", recvline);
        } else if(sendline[0] == '1') {
            printf("Insert the article id and quantity to buy (<id1>-<qty1>,<id2>-<qty2>,...): ");
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_BUFFER_SIZE, stdin);
            send(sockfd, sendline, strlen(sendline), 0);
            memset(recvline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recvline, MAX_BUFFER_SIZE, 0);
            recvline[received_bytes] = 0;
            printf("%s", recvline);
            memset(sendline, 0, MAX_BUFFER_SIZE);
            fgets(sendline, MAX_BUFFER_SIZE, stdin);
            send(sockfd, sendline, strlen(sendline), 0);
            memset(recvline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recvline, MAX_BUFFER_SIZE, 0);
            recvline[received_bytes] = 0;
            printf("%s", recvline);
        }
    }

    close(sockfd);

    return 0;
}