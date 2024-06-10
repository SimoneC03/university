#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PLAYERS_N 2 // Players number
#define MAX_CHANCES_PER_PLAYER 3 // Max chances per player
#define MAX_BUFFER_SIZE 300 // Max text size to send
#define MAX_PLAYER_NAME 100
#define MAX_WORD_SIZE 50

#include "server.h"

/* Return if the game has over and no player has still available chances */
short int isGameEnd(Player players[]) {
    short int res = 1; // init value: yes
    for(int i = 0; i < PLAYERS_N; i++) {
        if(players[i].chances != 0) res = 0;
    }
    return res;
}

/* Return a random word to guess */
char *getRandomWord() {
    srand(time(NULL));
    char words[5][MAX_WORD_SIZE] = {"choice", "advertising", "chocolate", "complication", "vegetable"};
    char *r = malloc(MAX_WORD_SIZE);
    strcpy(r, words[rand()%5]);
    return r;
}

/* Send a message using an open socket and return the number of bytes 
 * successfully sent */
ssize_t sendLine(int sockfd, char *mes, struct sockaddr_in dest_addr) {
    return sendto(sockfd, mes, strlen(mes), 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));
}

/* Return the index of the Player with the given info inside the `players` 
 * array if it has been registered, otherwise return -1 */
int getPlayerIndex(in_addr_t ip, in_port_t port, Player players[]) {
    for(int i = 0; i < PLAYERS_N; i++) {
        if(players[i].ip == ip && players[i].port == port) return i;
    }
    return -1;
}

/* Return NULL if the Player with the given info can enter the game, otherwise
 * return the error message */
char *canJoin(in_addr_t ip, char *name, in_port_t port, Player players[]) {
    char *res = malloc(100);
    strcpy(res, "The lobby is full. Please wait until the next game.\n");
    for(int i = 0; i < PLAYERS_N; i++) {
        if(players[i].ip == 0 && players[i].port == 0) {
            free(res);
            res = NULL;
            return res;
        }
        // check if addressing info or name already registered
        else if(players[i].ip == ip && players[i].port == port) {
            strcpy(res, "You've already joined the game!\n");
            return res;
        }
        else if (strcmp(players[i].name, name) == 0) {
            strcpy(res, "The name has been already taken. Please try to change name.\n");
            return res;
        }
    }
    return res;
}

/* Return the current word structure with a given `chars` array of guessed letters */
char *getWordStructure(char *word, char chars[]) {
    char *r = strdup(word);
    const int m = strlen(word);
    const int n = strlen(chars);
    for(int i = 0; i < m; i++) {
        r[i] = '_';
        for(int j = 0; j < n; j++) {
            if(chars[j] == word[i]) r[i] = chars[j];
        }
    }
    return r;
}

int main(int argc, char **argv) {
    // Local (server) and remote (incoming requests) addresses
    struct sockaddr_in local_addr, remote_addr;
    socklen_t remoteaddr_len = sizeof(struct sockaddr_in);

    // Text received from the players
    char buffer[MAX_BUFFER_SIZE];
    int recbytes = 0;

    // Socket descriptor
    int sockfd;

    Player players[PLAYERS_N];
    int players_len = 0; // Joined players counter
    int turn = -1; // index of the current player

    if(argc < 2) {
        printf("Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("An error has occurred while socket opening\n");
        return -1;
    }

    // set all bytes to 0
    memset(&local_addr, 0, sizeof(local_addr));
    // IPv4 address family
    local_addr.sin_family = AF_INET;
    // convert the port number from host byte order to network byte order
    local_addr.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET, "0.0.0.0", &local_addr.sin_addr);

    // try to bind the socket connection to the specified local address and port
    if(bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        printf("Connection refused. Insert a different port number\n");
        return -1;
    }

    // register players
    for(int i = 0; i < PLAYERS_N; i++) {
        printf("Wait for players...\n");
        memset(buffer, 0, MAX_BUFFER_SIZE-1);
        recbytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &remoteaddr_len);
        buffer[recbytes-1] = 0; // -1 to remove new line char
        char *check = canJoin(remote_addr.sin_addr.s_addr, buffer, remote_addr.sin_port, players);
        if(check == NULL) {
            // register new player
            memset(&players[players_len], 0, sizeof(Player));
            players[players_len].ip = remote_addr.sin_addr.s_addr;
            strcpy(players[players_len].name, buffer);
            players[players_len].port = remote_addr.sin_port;
            players[players_len].chances = 3;
            players_len++;
            printf("Player %s joined the game\n", buffer);
            sendLine(sockfd, "registered", remote_addr);
        } else {
            sendLine(sockfd, check, remote_addr);
            free(check);
        }
    }

    // start the game
    char *word_to_guess = getRandomWord();
    printf("\nGame has started!\nWord to guess: %s\n\n", word_to_guess);
    turn = 0;
    char letters[MAX_WORD_SIZE];
    int found_letters = 0 ;
    while(!isGameEnd(players)) {

        // skip players with 0 chances
        while (players[turn].chances == 0) {
            turn = (turn + 1) % players_len;
        }

        printf("%s's turn\n", players[turn].name);
        // prepare remote_addr structure
        remote_addr.sin_addr.s_addr = players[turn].ip;
        remote_addr.sin_port = players[turn].port;

        // send the word structure to the player whose turn it is
        char *wstruct = getWordStructure(word_to_guess, letters);
        memset(buffer, 0, MAX_BUFFER_SIZE-1);
        sprintf(buffer, "Word: %s - Chances left: %d/%d - Players: %d/%d\nInsert a letter or a complete word: ", wstruct, players[turn].chances, MAX_CHANCES_PER_PLAYER, players_len, PLAYERS_N);
        sendLine(sockfd, buffer, remote_addr);
        free(wstruct);

        // wait for response
        memset(buffer, 0, MAX_BUFFER_SIZE-1);
        recbytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &remoteaddr_len);
        buffer[recbytes] = 0;
        const int check = getPlayerIndex(remote_addr.sin_addr.s_addr, remote_addr.sin_port, players);
        if(check == turn) {
            // received buffer contains also the new line char at the end
            if(strlen(buffer) > 2) {
                // Player try to guess the word
                // remove from buffer the new line char
                buffer[strlen(buffer)-1] = '\0';
                if(strcmp(buffer, word_to_guess) == 0) {
                    // word guessed
                    memset(buffer, 0, MAX_BUFFER_SIZE-1);
                    sprintf(buffer, "The word was %s\nPlayer %s has won the game!\n", word_to_guess, players[turn].name);
                    for(int i = 0; i < players_len; i++) {
                        remote_addr.sin_addr.s_addr = players[i].ip;
                        remote_addr.sin_port = players[i].port;
                        sendLine(sockfd, buffer, remote_addr);
                    }
                    printf("Player %s has won the game\n", players[turn].name);
                    break;
                } else {
                    // wrong word
                    players[turn].chances--;
                    sendLine(sockfd, "Wrong word\n", remote_addr);
                }
            } else {
                // Player try to guess a letter
                if(strchr(word_to_guess, buffer[0])) {
                    // letter guessed
                    sendLine(sockfd, "Letter guessed!\n", remote_addr);
                    found_letters++;
                    letters[found_letters-1] = buffer[0];
                } else {
                    // wrong letter
                    players[turn].chances--;
                    sendLine(sockfd, "Wrong letter\n", remote_addr);
                }
            }
            // check if player has lost the game
            if(players[turn].chances == 0) {
                printf("Player %s has lost\n", players[turn].name);
                // send disconnection signal
                sendLine(sockfd, "--exit\n", remote_addr);
            }
        } else if(check != -1){
            sendLine(sockfd, "You cannot play. Wait your turn\n", remote_addr);
        } else {
            sendLine(sockfd, "You cannot play. Tha game has already started\n", remote_addr);
        }
        
        turn = (turn + 1) % players_len;
    }

    if(isGameEnd(players)) fputs("GAME OVER\n", stdout);

    // close the socket connection
    close(sockfd);
    // free allocated memory
    free(word_to_guess);

    return 0;
}