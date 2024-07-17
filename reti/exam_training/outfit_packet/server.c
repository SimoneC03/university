#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define DRESSES_N 5
#define MAX_BUFFER_SIZE 1000

typedef struct Dress {
    char name[100];
    char size[5];
    float price;
    unsigned int qty;
} Dress;

char *getDresses(Dress dresses[]) {
    char *res = malloc(MAX_BUFFER_SIZE);
    if(res == NULL) {
        perror("Error occurred while allocating memory\n");
        return NULL;
    }
    for(int i = 0; i < DRESSES_N; i++) {
        // check if a dress is set
        if(strlen(dresses[i].name) > 0) {
            char dress[sizeof(Dress)+200] = {0};
            sprintf(dress, "Article %d\nName: %s\nSize: %s\nPrice: %.2f\nQuantity: %d\n\n", i+1, dresses[i].name, dresses[i].size, dresses[i].price, dresses[i].qty);
            strcat(res, dress);
        }
    }
    return res;
}

int main(int argc, char **argv) {
    int sockfd, newsockfd, received_bytes = 0;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t s_len = sizeof(struct sockaddr_in);
    char msg[MAX_BUFFER_SIZE];
    Dress dresses[DRESSES_N];
    dresses[0] = (Dress){ .name= "Dress0" , .size = "S" , .price = 55.4, .qty = 4};
    dresses[1] = (Dress){ .name= "Dress1" , .size = "XL" , .price = 11.40, .qty = 1};
    dresses[2] = (Dress){ .name= "Dress2" , .size = "XXL" , .price = 85.4, .qty = 2};
    dresses[3] = (Dress){ .name= "Dress3" , .size = "M" , .price = 19.4, .qty = 1};
    dresses[4] = (Dress){ .name= "Dress4" , .size = "M" , .price = 35.4, .qty = 1};

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
    
    listen(sockfd, 5);

    for(;;) {
        newsockfd = accept(sockfd, (struct sockaddr *)&remote_addr, &s_len);
        int pid = fork();
        if(pid == 0) {
            close(sockfd);
            for(;;) {
                // receive selected action
                received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE, 0);
                msg[received_bytes] = 0;
                // end communcation
                if(strcmp(msg, "END\n") == 0) {
                    return -1;
                } else if(msg[0] == '0') {
                    // View all dresses
                    char *dresses_list = getDresses(dresses);
                    send(newsockfd, dresses_list, strlen(dresses_list), 0);
                    free(dresses_list);
                } else if(msg[0] == '1') {
                    // Buy one/more clothes
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE, 0);
                    msg[received_bytes] = 0;
                    // read requested dresses
                    Dress requested_dresses[DRESSES_N];
                    for(int i = 0; i < DRESSES_N; i++) requested_dresses[i].name[0] = 0;
                    char *requested = strtok(msg, ",");
                    while (requested != NULL) {
                        int id, qty;
                        sscanf(requested, "%d-%d", &id, &qty);
                        for(int i = 0; i < DRESSES_N; i++) {
                            if(i == id-1) {
                                strcpy(requested_dresses[i].name, dresses[i].name);
                                requested_dresses[i].price = dresses[i].price;
                                requested_dresses[i].qty = qty;
                                strcpy(requested_dresses[i].size, dresses[i].size);
                            }
                        }
                        requested = strtok(NULL, ",");
                    }
                    memset(msg, 0, MAX_BUFFER_SIZE);
                    strcpy(msg, "Requested articles:\n");
                    char *rdresses = getDresses(requested_dresses);
                    strcat(msg, rdresses);
                    strcat(msg, "Are you sure you want to confirm the operation?\n");
                    free(rdresses);
                    send(newsockfd, msg, MAX_BUFFER_SIZE, 0);
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE, 0);
                    msg[received_bytes] = 0;
                    if(strcmp(msg, "Yes\n") == 0) {
                        short int error = 0;
                        for(int i = 0; i < DRESSES_N; i++) {
                            // check if request dress is set, if its quantity is available
                            if( strlen(requested_dresses[i].name) > 0 && requested_dresses[i].qty > dresses[i].qty) {
                                sprintf(msg, "Quantity requested for the article %d is not available. Only %d items left, requested is %d\n", i+1, dresses[i].qty, requested_dresses[i].qty);
                                send(newsockfd, msg, MAX_BUFFER_SIZE, 0);
                                error = -1;
                                break;
                            }
                        }
                        if(error == 0) {
                            for(int i = 0; i < DRESSES_N; i++) {
                                fflush(stdout);
                                if(strlen(requested_dresses[i].name) > 0) {
                                    dresses[i].qty -= requested_dresses[i].qty;}
                            }
                            send(newsockfd, "Operation confirmed\n", 50, 0);
                        }                        
                    } else send(newsockfd, "Operation canceled\n", 50, 0);
                }
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            printf("Client %s:%d has ended the communication\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
            close(newsockfd);
        }
    }

    close(sockfd);

    return 0;
}