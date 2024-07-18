#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1000

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in remote_addr;
    char sendline[MAX_BUFFER_SIZE];
    char recline[MAX_BUFFER_SIZE];
    socklen_t len = sizeof(struct sockaddr_in);
    int received_bytes = 0;
    
    if(argc != 3) {
        printf("Error. Please insert IP and port\n");
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("Error occurred while opening socket\n");
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
    remote_addr.sin_port = htons(atoi(argv[2]));

    sendto(sockfd, "Connected\n", 11, 0, (struct sockaddr *)&remote_addr, len);
    received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
    recline[received_bytes] = 0;
    printf("%s", recline);

    for(;;) {
        printf("Wait your turn\n");
        received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        recline[received_bytes] = 0;
        printf("%s", recline);
        if(strstr(recline, "won") != NULL) return 1;
        for(;;) {
            fgets(sendline, MAX_BUFFER_SIZE, stdin);
            // prepare the inserted character and a random jackpot space separated
            sendline[1] = 0;
            char tmp[20];
            srand(time(NULL));
            sprintf(tmp, " %d", (rand() % 9000) +1000);
            strcat(sendline, tmp);
            sendto(sockfd, sendline, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
            // wait for character guess result
            received_bytes = recvfrom(sockfd, recline, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            recline[received_bytes] = 0;
            printf("%s", recline);
            if(strstr(recline, "not contained") != NULL) {
                break;
            }
        }
    }

    printf("End of communication\n");
    close(sockfd);

    return 0;
}