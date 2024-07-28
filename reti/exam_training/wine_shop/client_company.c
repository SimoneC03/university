#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 10000

typedef struct Item {
    char company[100];
    size_t id;
    char name[100];
    unsigned int qty;
    float price;
} Item;

size_t senddata(int sockfd, char  *str) {
    return send(sockfd, str, strlen(str), 0);
}

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in6 dest_addr;
    char sendline[MAX_BUFFER_SIZE];
    char recline[MAX_BUFFER_SIZE];

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
    dest_addr.sin6_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    // send company name required for the operations
    senddata(sockfd, "company1");

    for(;;) {
        memset(recline, 0, MAX_BUFFER_SIZE);
        received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
        recline[received_bytes] = 0;
        printf("%s", recline);
        fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
        senddata(sockfd, sendline);
        if(sendline[0] == '3') {
            printf("Ending connection\n");
            return 0;
        } else if(sendline[0] == '0') {
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
            recline[received_bytes] = 0;
            printf("%s", recline);
            // send confirmation received
            senddata(sockfd, "received");
        } else if(sendline[0] == '1') {
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
            recline[received_bytes] = 0;
            printf("%s", recline);
            fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
            senddata(sockfd, sendline);
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
            recline[received_bytes] = 0;
            printf("%s", recline);
        } else if(sendline[0] == '2') {
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
            recline[received_bytes] = 0;
            printf("%s", recline);
            fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
            senddata(sockfd, sendline);
            memset(recline, 0, MAX_BUFFER_SIZE);
            received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
            recline[received_bytes] = 0;
            printf("%s", recline);
            // send confirmation received
            senddata(sockfd, "received");
        }
    }

    close(sockfd);

    return 0;
}