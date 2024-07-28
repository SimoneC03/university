#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1000

typedef struct Player {
    char name[100];
    struct sockaddr_in addr;
} Player;

void sendbroadcast(int sockfd, char *str, Player players[2]) {
    for(int i = 0; i < 2; i++) {
        sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&players[i].addr, sizeof(struct sockaddr));
    }
}

char *getMatrix(int matrix[6][7]) {
    char *res = malloc(MAX_BUFFER_SIZE);
    memset(res, 0, strlen(res));
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
            char tmp[5];
            sprintf(tmp, " %*d", 2, matrix[i][j]);
            strcat(res, tmp);
        }
        strcat(res, "\n");
    }
    return res;
}

short int fillMatrix(int matrix[6][7], int column, int turn) {
    if(column > 7 || column < 1) return -1;
    for(int i = 5; i >= 0; i--) {
        if(matrix[i][column-1] == -1) {
            printf("column %d of row %d changed with %d\n", column, i, turn);
            matrix[i][column-1] = turn;
            return 1;
        }
    }
    return 0;
}

short int checkWinnerHorizontal(int matrix[6][7]) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            int c = 0;
            for(int k = 0; k < 4; k++) {
                if(matrix[i][k+j] != -1 && matrix[i][k+j] == matrix[i][j]) c++;
            }
            if(c == 4) return 1;
        }
    }
    return 0;
}

short int checkWinnerVertical(int matrix[6][7]) {
    for(int j = 0; j < 7; j++) {
        for(int i = 0; i < 3; i++) {
            int c = 0;
            for(int k = 0; k < 4; k++) {
                if(matrix[k+i][j] != -1 && matrix[k+i][j] == matrix[i][j]) c++;
            }
            if(c == 4) return 1;
        }
    }
    return 0;
}

short int checkWinner(int matrix[6][7]) {
    return (checkWinnerVertical(matrix)==1 || checkWinnerHorizontal(matrix)==1) ? 1 : 0;
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char msg[MAX_BUFFER_SIZE];
    int received_bytes = 0;
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

    Player players[2];
    int matrix[6][7] = {[0 ... 5] = {[0 ... 6] = -1}};

    for(int i = 0; i < 2; i++) {
        memset(msg, 0, sizeof(msg));
        received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&players[i].addr, &len);
        msg[received_bytes] = 0;
        strcpy(players[i].name, msg);
    }

    sendbroadcast(sockfd, "Game has started!\n", players);

    int turn = 0;

    for(;;) {
        memset(msg, 0, sizeof(msg));
        if(checkWinner(matrix) == 1) {
            sprintf(msg, "Player %d won the game!\n", (turn+1)%2);
            sendbroadcast(sockfd, msg, players);
            return 1;
        }
        char *m = getMatrix(matrix);
        sprintf(msg, "It's your turn\n%s\nWhich column do you choose? ", m);
        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&players[turn].addr, len);
        free(m);
        receive_move:
        memset(msg, 0, sizeof(msg));
        received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&players[turn].addr, &len);
        msg[received_bytes] = 0;
        short int res = fillMatrix(matrix, atoi(msg), turn);
        if(res != 1) {
            sendto(sockfd, "Column is not valid or is full.\nPlease choose another one: ", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].addr, len);
            goto receive_move;
        } else {
            sendto(sockfd, "Done\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&players[turn].addr, len);
            turn = (turn+1)%2;
        }
    }

    printf("End of comnunication\n");
    close(sockfd);

    return 0;
}