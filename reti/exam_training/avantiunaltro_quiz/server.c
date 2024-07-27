#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define QUESTIONS_N 3
#define MAX_BUFFER_SIZE 1000

int senddata(int sockfd, char *str) {
    printf("Sending %ld bytes of data\n", strlen(str));
    return send(sockfd, str, strlen(str), 0);
}

int main(int argc, char **argv) {
    int sockfd, newsockfd, received_bytes = 0;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t s_len = sizeof(struct sockaddr_in);
    char msg[MAX_BUFFER_SIZE];
    char questions[QUESTIONS_N][200] = {"Qual è la capitale d'Italia? Milano o Roma?\n", "Quanti elementi ci sono nella tavola periodica? 74 o 118?\n", "Che studio di videogiochi ha prodotto GTA? Rockstar Games o Ubisoft?\n"};
    // answers to the questions must be wrong
    char answers[QUESTIONS_N][100] = {"Milano\n", "74\n", "Ubisoft\n"};

    if(argc != 2) {
        printf("Insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error while socket opening\n");
        return -1;
    }

    memset(&local_addr, 0, s_len);
    local_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &local_addr.sin_addr);
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, s_len) < 0) {
        printf("Error while binding\n");
        return -1;
    }
    
    listen(sockfd, 1);

    char player[100];
    int jackpot = 0;
    srand(time(NULL));

    for(;;) {
        newsockfd = accept(sockfd, (struct sockaddr *)&remote_addr, &s_len);

        // register player and generate a new jackpot
        received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
        msg[received_bytes] = 0;
        strcpy(player, msg);
        jackpot = rand() % 290000 + 10000;
        sprintf(msg, "%s stai giocando per un importo di %d €. Iniziamo?\n", player, jackpot);
        senddata(newsockfd, msg);
        // receive confirmation
        memset(msg, 0, sizeof(msg));
        received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
        msg[received_bytes] = 0;

        int pid = fork();
        if(pid == 0) {
            close(sockfd);
            for(;;) {
                ask_questions:
                for(int i = 0; i < QUESTIONS_N; i++) {
                    memset(msg, 0, sizeof(msg));
                    if(i == 0) {
                        sprintf(msg, "Montepremi attuale: %d €\nDomanda %d: %s", jackpot, i+1, questions[i]);
                    } else {
                        sprintf(msg, "Domanda %d: %s", i+1, questions[i]);
                    }
                    int n = senddata(newsockfd, msg);
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes] = 0;
                    if(strcmp(msg, answers[i]) != 0) {
                        jackpot -= 10000;
                        if(jackpot <= 0) {
                            senddata(newsockfd, "Hai perso!\n");
                            return 0;
                        } else {
                            senddata(newsockfd, "Risposta sbagliata\n");
                            goto ask_questions;
                        }
                    } else {
                        senddata(newsockfd, "Giusto, prossima domanda\n");
                    }
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes] = 0;
                }
                sprintf(msg, "Congratulazioni! Hai viinto %d €\n", jackpot);
                senddata(newsockfd, msg);
                return 0;
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            printf("Gioco terminato\n");
            close(newsockfd);
        }
    }

    close(sockfd);

    return 0;
}