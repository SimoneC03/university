#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_PHRASE_SIZE 100
#define PLAYERS_N 2

typedef struct Player {
    struct sockaddr_in client;
    unsigned int jackpot;
} Player;

char *getSecretPhrase() {
    char phrases[3][MAX_PHRASE_SIZE] = {"computer networks lab exam", "when the rubber hits the road", "a day late and a dollar short"};
    char *res = malloc(MAX_PHRASE_SIZE);
    if(res == NULL) {
        perror("Error occurreed while allocating memory\n");
        return NULL;
    }
    srand(time(NULL));
    strcpy(res, phrases[rand()%3]);
    return res;
}

char *registerPlayer(Player players[], int *players_n, struct sockaddr_in client) {
    if(*players_n == PLAYERS_N) return "Lobby is full. The game is starting.\n";
    for(int i = 0; i < PLAYERS_N; i++) {
        if(players[i].client.sin_addr.s_addr == client.sin_addr.s_addr && players[i].client.sin_port == client.sin_port) return "You have already been registered before. The game will start soon.\n";
    }
    players[*players_n].jackpot = 0;
    players[*players_n].client = client;
    (*players_n)++;
    return "You have been registered correctly\n";
}

char *getPhraseStructure(char *secret_phrase, char *guessed_chars) {
    char *res = malloc(MAX_PHRASE_SIZE);
    const int n = strlen(secret_phrase);
    const int m = strlen(guessed_chars);
    for(int i = 0; i < n; i++) {
        res[i] = '_';
        for(int j = 0; j < m; j++) {
            if(secret_phrase[i] == guessed_chars[j]) {
                res[i] = secret_phrase[i]; 
                break;
            }
        }
    }
    return res;
}

unsigned int getOccurrences(char c, char *str) {
    unsigned int occurs = 0;
    const int n = strlen(str);
    for(int i = 0; i < n; i++) 
        if(str[i] == c) occurs++;
    return occurs;
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char msg[MAX_BUFFER_SIZE];
    int received_bytes = 0;
    char *secret_phrase = getSecretPhrase();
    char guessed_chars[MAX_PHRASE_SIZE] = {0};
    unsigned int guessed_chars_n = 0;
    Player players[PLAYERS_N];
    int players_n = 0;

    if(argc != 2) {
        printf("Error. Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error occurred while opening socket\n");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
        printf("Error. Please insert a different port number\n");
        return -1;
    }

    for(int i = 0; i < PLAYERS_N; i++) {
        received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        msg[received_bytes] = 0;
        char *res = registerPlayer(players, &players_n, remote_addr);
        sendto(sockfd, res, strlen(res), 0, (struct sockaddr *)&remote_addr, len);
    }

    int turn = 0;
    for(;;) {
        char *pstruct = getPhraseStructure(secret_phrase, guessed_chars);
        sprintf(msg, "It's your turn\nPhrase to guess is:\n%s\n", pstruct);
        free(pstruct);
        sendto(sockfd, msg, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].client, len);
        unsigned int occurs;
        char c;
        unsigned int jackpot;
        for(;;) {
            // wait for character and random jackpot
            received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&players[turn].client, &len);
            msg[received_bytes] = 0;
            sscanf(msg, "%c %d", &c, &jackpot);
            occurs = getOccurrences(c, secret_phrase);
            if(occurs == 0) break;
            // check if character has already been guessed before
            short int check = -1;
            for(int i = 0; i < MAX_PHRASE_SIZE; i++)
                if(guessed_chars[i] == c) {
                    check = i;
                }
            if(check == -1) {
                jackpot = jackpot*occurs;
                players[turn].jackpot += jackpot;
                guessed_chars[guessed_chars_n] = c;
                guessed_chars_n++;
                char *pstruct = getPhraseStructure(secret_phrase, guessed_chars);
                // check if has won the game
                if(strchr(pstruct, '_') == NULL) {
                    sprintf(msg, "\nCharacter guessed correctly!\nYou won the game!\n");
                    sendto(sockfd, msg, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].client, len);
                    sprintf(msg, "\nPlayer %d won the game!\nHis jackpot is %d€\nPhrase was: %s", turn+1, players[turn].jackpot, pstruct);
                    printf("%s", msg);
                    for(int i = 0; i < PLAYERS_N; i++) sendto(sockfd, msg, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[i].client, len);
                    free(pstruct);
                    return 1;
                } else {
                    sprintf(msg, "\nCharacter guessed correctly!\nYour jackpot is %d€\nPhrase to guess is:\n%s\nTry to guess another one: ", players[turn].jackpot, pstruct);
                    sendto(sockfd, msg, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].client, len);
                    free(pstruct);
                }
            } else {
                char *pstruct = getPhraseStructure(secret_phrase, guessed_chars);
                sprintf(msg, "\nThat character has already been guessed before!\nPhrase to guess is:\n%s\nTry to guess another one: ", pstruct);
                free(pstruct);
                sendto(sockfd, msg, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].client, len);
            }
        }
        sprintf(msg, "\nThat character is not contained in the phrase\nYour jackpot is %d€\nIt's player %d's turn.\n", players[turn].jackpot, ((turn+1) % PLAYERS_N)+1);
        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&players[turn].client, len);
        turn = (turn+1) % PLAYERS_N;
    }

    printf("End of comnunication\n");
    close(sockfd);
    free(secret_phrase);

    return 0;
}