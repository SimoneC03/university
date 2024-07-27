#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1000

int senddata(int sockfd, char *str) {
    return send(sockfd, str, strlen(str), 0);
}

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in dest_addr;
    char sendline[MAX_BUFFER_SIZE];
    char recline[MAX_BUFFER_SIZE];

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

    // send name for registrations
    senddata(sockfd, "Giocatore1");
    received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
    recline[received_bytes] = 0;
    // send confirmation to start the game
    printf("%s", recline);
    fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
    senddata(sockfd, sendline);

    for(;;) {
        memset(recline, 0, sizeof(recline));
        received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
        recline[received_bytes] = 0;
        printf("%s (%d bytes)", recline, received_bytes);
        // check if it has not won yet
        if(strstr(recline, "Congratulazioni") != NULL && strchr(recline, '?') == NULL) return 0;
        fgets(sendline, MAX_BUFFER_SIZE-1, stdin);
        senddata(sockfd, sendline);
        memset(recline, 0, sizeof(recline));
        received_bytes = recv(sockfd, recline, MAX_BUFFER_SIZE-1, 0);
        recline[received_bytes] = 0;
        printf("%s", recline);
        if(strstr(recline, "perso") != NULL) return -1;
        else senddata(sockfd, "ok");
    }

    close(sockfd);

    return 0;
}