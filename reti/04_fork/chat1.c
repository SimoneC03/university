#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
    Two ports for managing sending and receiving channels

    args: <target_ip> <rcv_port> <send_port>
    args: <target_ip> <send_port> <rcv_port>
*/

int main(int argc, char **argv) {
    int sockfd, received_bytes = 0;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in); 
    char msg[1000];

    if(argc < 4) {
        printf("Error. Please insert all the parameters\n");
        return -1;
    }

    if(fork()) {
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            printf("Error while socket opening\n");
            return -1;
        }
        memset(&local_addr, 0, len);
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(atoi(argv[2]));

        if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
            printf("Error occured while binding\n");
            return -1;
        }

        for(;;) {
            // manage reception
            received_bytes = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&remote_addr, &len);
            msg[received_bytes] = 0;
            printf("IP = %s, port = %d, msg = %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), msg);
            if(strcmp(msg, "end\n") == 0) break;
        }
        printf("End of communication\n");
        return 0;
    } else {
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            printf("Error while socket opening\n");
            return -1;
        }
        memset(&local_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
        remote_addr.sin_port = htons(atoi(argv[2]));
        
        while(fgets(msg, 1000, stdin) != NULL) {
            sendto(sockfd, msg, received_bytes, 0, (struct sockaddr *)&remote_addr, len);
            if(strcmp(msg, "end\n") == 0) break;
        }
        
        printf("End of communication\n");
        return 0;
    }
}