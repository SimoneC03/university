#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_BUFFER_SIZE 500

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in6 server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char recline[MAX_BUFFER_SIZE];
    char sendline[MAX_BUFFER_SIZE];

    
    if(argc != 3) {
        printf("Please, run like ./program <server_ip> <server_port>\n");
        return -1;
    }

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
        printf("Error while creating socket\n");
        return -1;
    }

    memset(&server_addr, 0, addr_len);
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(atoi(argv[2]));
    inet_pton(AF_INET6, argv[1], &server_addr.sin6_addr);

    if((connect(sockfd, (struct sockaddr *)&server_addr, addr_len)) == -1) {
        printf("Error while connecting to the server\n");
        return -1;
    }
    printf("Server connection estabilished\n");

    do {
        // receive products list
        memset(recline, 0, MAX_BUFFER_SIZE);
        received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE, 0);
        recline[received_bytes] = 0;
        fputs(recline, stdout);
        printf("Please, insert a product ID and quantity (<id>, <qty>)\n");
        memset(sendline, 0, MAX_BUFFER_SIZE);
        fgets(sendline, MAX_BUFFER_SIZE, stdin);
        // send product and its quantity
        send(sockfd, sendline, MAX_BUFFER_SIZE, 0);
        memset(recline, 0, MAX_BUFFER_SIZE);
        received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE, 0);
        recline[received_bytes] = 0;
        printf("Server has returned the product:\n%s\n", recline);
        printf("press q to quit, c to continue\n");
        memset(sendline, 0, MAX_BUFFER_SIZE);
        fgets(sendline, 2, stdin);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        send(sockfd, sendline, MAX_BUFFER_SIZE, 0);
    } while(sendline[0] == 'c');

    send(sockfd, "end", MAX_BUFFER_SIZE, 0);
    close(sockfd);

    return 0;
}