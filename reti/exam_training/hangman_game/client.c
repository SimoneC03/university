#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_PLAYER_NAME 100
#define MAX_SENDLINE_SIZE 200
#define MAX_RECLINE_SIZE 500

int main(int argc, char **argv) {
    // Destination (server) address
    struct sockaddr_in dest_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    // Client name to enter the game
    char name[MAX_PLAYER_NAME]; 
    // Socket descriptor
    int sockfd; 
    // Line to send
    char sendline[MAX_SENDLINE_SIZE];
    // Line received 
    char recline[MAX_RECLINE_SIZE]; 
    // Keep track of received bytes for each request
    int recbytes = 0; 

    if(argc < 3) {
        printf("Please insert destination IP and port\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("An error has occurred while socket opening\n");
        return -1;
    }

    // Set all bytes to 0
    memset(&dest_addr, 0, sizeof(dest_addr));
    // IPv4 address family
    dest_addr.sin_family = AF_INET;
    // Convert address to binary network format
    inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr));
    // Convert the port number from host byte order to network byte order
    dest_addr.sin_port = htons(atoi(argv[2]));

    printf("Insert your name to enter a game (max 100 chars): ");
    while(fgets(sendline, MAX_SENDLINE_SIZE, stdin) != NULL) {
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&dest_addr, addr_len);
        recbytes = recvfrom(sockfd, recline, MAX_RECLINE_SIZE-1, 0, (struct sockaddr *)&dest_addr, &addr_len);
        recline[recbytes] = 0;
        // exit from game
        if(strcmp(sendline, "--exit\n") == 0) break;

        fputs(recline, stdout);
    }

    // close the socket connection
    close(sockfd);
    return 0;
}