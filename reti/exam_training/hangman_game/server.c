#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PLAYERS_N 2 // Players number
#define MAX_CHANCES_PER_PLAYER 3 // Max chances per player
#define MAX_BUFFER_SIZE 200 // Max text size to send
#define MAX_PLAYER_NAME 100

typedef struct Client {
    char name[MAX_PLAYER_NAME];
    char ip[18];
    uint16_t port;
} Client;

/* Send a message using an open socket and return the number of bytes successfully sent */
ssize_t sendLine(int sockfd, char *mes, struct sockaddr_in dest_addr) {
    return sendto(sockfd, mes, strlen(mes), 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));
}

/* Return if the client with the given info can play the game */
bool canPlay(char *ip, uint16_t port, Client users[]) {
    for(int i = 0; i < PLAYERS_N; i++) {
        if(strcmp(users[i].ip, ip) == 0 && users[i].port == port) return true;
    }
    return false;
}

/* Return if the client with the given info can enter the game */
bool canJoin(char *ip, char *name, uint16_t port, Client users[]) {
    bool canJoin = false;
    for(int i = 0; i < PLAYERS_N; i++) {
        if(strcmp(users[i].ip, "") == 0) canJoin = true;
        // check if addressing info or name already registered
        else if((strcmp(users[i].ip, ip) == 0 && users[i].port == port) || strcmp(users[i].name, name) == 0) return false;
    }
    return canJoin;
}

int main(int argc, char **argv) {
    // Local (server) and remote (incoming requests) addresses
    struct sockaddr_in local_addr, remote_addr;
    // Text received from the clients
    char recline[MAX_BUFFER_SIZE];
    int recbytes = 0;
    // Socket descriptor
    int sockfd;

    Client users[PLAYERS_N];
    int users_len = 0; // Joined users counter

    int turn = -1; // Keep track of the current turn
    
    socklen_t len = sizeof(struct sockaddr_in);

    if(argc < 2) {
        printf("Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("An error has occurred while socket opening\n");
        return -1;
    }

    // set all bytes to 0
    memset(&local_addr, 0, len);
    // IPv4 address family
    local_addr.sin_family = AF_INET;
    // convert the port number from host byte order to network byte order
    local_addr.sin_port = htons(atoi(argv[1]));

    // try to bind the socket connection to the specified local address and port
    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
        printf("Connection refused. Insert a different port number\n");
        return -1;
    }

    // infinite loop to keep listening for incoming requests
    for(;;) {
        // read and print bytes from incoming socket request
        recbytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        recline[recbytes] = 0;
        char *ip = inet_ntoa(remote_addr.sin_addr);
        uint16_t port = ntohs(remote_addr.sin_port);
        
        if(users_len == PLAYERS_N) {
            // start the game
            turn = 0;
        }

        if(turn != -1) {
            // game has started
            if(canPlay(ip, port, users)) {
                fputs(recline, stdout);
                sendLine(sockfd, "msg received\n", remote_addr);
            } else {
                sendLine(sockfd, "You cannot join. The game has already started\n", remote_addr);
            }
        } else {
            if(canPlay(ip, port, users)) {
                char *temp = malloc(100);
                sprintf(temp, "Please, wait until the lobby is full.\nPlayers: %d/%d\n", users_len, PLAYERS_N);
                sendLine(sockfd, temp, remote_addr);
                free(temp);
            } else {
                // game has not started
                if(canJoin(ip, recline, port, users)) {
                    strcpy(users[users_len].ip, ip);
                    strcpy(users[users_len].name, recline);
                    users[users_len].port = port;
                    users_len++;
                    printf("User %d joined the game\n", users_len-1);
                    sendLine(sockfd, "Joined!\n", remote_addr);
                } else {
                    // already joined or is lobby full
                    printf("Player %s can not join the game\n", recline);
                    sendLine(sockfd, "You cannot join. Try to choose another name\n", remote_addr);
                }
            }
        }
    }

    // close the socket connection
    close(sockfd);

    return 0;
}