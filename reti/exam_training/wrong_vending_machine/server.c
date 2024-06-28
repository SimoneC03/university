#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_BUFFER_SIZE 500
#define MAX_CONNECTIONS 5
#define MAX_PRODUCTS 5

typedef struct Product {
    int id;
    char name[100];
    float price;
    int qty;
} Product;

char *getProducts(Product *products) {
    char *res = malloc(MAX_BUFFER_SIZE);
    for(int i = 0; i < MAX_PRODUCTS; i++) {
        char *line = malloc((MAX_BUFFER_SIZE/MAX_PRODUCTS)-1);
        sprintf(line, "%d, %s, %f, %d\n", products[i].id, products[i].name, products[i].price, products[i].qty);
        strcat(res, line);
    }
    return res;
}

int main(int argc, char **argv) {
    int sockfd, newsockfd, received_bytes = 0;
    struct sockaddr_in6 local_addr, remote_addr;
    socklen_t addr_len = sizeof(local_addr);
    char recline[MAX_BUFFER_SIZE];
    char sendline[MAX_BUFFER_SIZE];
    Product products[5];
    for(int i = 0; i < 5; i++) {
        products[i].id = i;
        sprintf(products[i].name, "%s%d", "product", i);
        products[i].price = 3*(rand()%5);
        products[i].qty = (1+i+(rand()%5))*i;
    }

    
    if(argc != 2) {
        printf("Please, run like ./program <server_port>\n");
        return -1;
    }

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
        printf("Error while creating socket\n");
        return -1;
    }

    memset(&local_addr, 0, addr_len);
    local_addr.sin6_family = AF_INET6;
    local_addr.sin6_port = htons(atoi(argv[1]));

    if((bind(sockfd, (struct sockaddr *)&local_addr, addr_len)) == -1) {
        printf("Error while binding\n");
        return -1;
    }

    printf("Waiting for connections at port %s...\n", argv[1]);
    listen(sockfd, MAX_CONNECTIONS);

    for(;;) {
        newsockfd = accept(sockfd, (struct sockaddr *)&remote_addr, &addr_len);
        char ipv6_addr[INET6_ADDRSTRLEN]; // remote ipv6 address in readable form
        inet_ntop(AF_INET6, &remote_addr.sin6_addr, ipv6_addr, INET6_ADDRSTRLEN);
        printf("New connection estabilished with %s:%d\n", ipv6_addr, ntohs(remote_addr.sin6_port));

        if(fork() == 0) {
            close(sockfd);

            for(;;) {
                printf("Sending products list\n");
                char *prod_list = getProducts(products);
                if((send(newsockfd, prod_list, MAX_BUFFER_SIZE, 0)) < 1) {
                    printf("Error while sending products list\n");
                    return -1;
                }

                memset(recline, 0, MAX_BUFFER_SIZE);
                received_bytes = recv(newsockfd, recline, MAX_BUFFER_SIZE, 0);
                recline[received_bytes] = 0;
                if(strcmp(recline, "end") == 0) {
                    printf("End of communication\n");
                    return -1;
                } else {
                    printf("Chosen from the client: %s\n", recline);
                    // read selected product information
                    int prod_id, prod_qty;
                    sscanf(recline, "%d, %d", &prod_id, &prod_qty);
                    // generate new prod id and qty different from those selected
                    int new_id, new_qty;
                    srand(time(NULL));
                    new_id = rand() % MAX_PRODUCTS;
                    new_qty = rand() % MAX_PRODUCTS;
                    if(new_id == prod_id) new_id++;
                    if(new_qty == prod_qty) new_qty++;
                    for(int i = 0; i < MAX_PRODUCTS; i++) {
                        if(products[i].id == new_id) {
                            memset(sendline, 0, MAX_BUFFER_SIZE);
                            sprintf(sendline, "%d, %s, %f, %d\n", new_id, products[i].name, products[i].price, new_qty);
                            printf("Send random product with id %d to the client\n", new_id);
                            fputs(sendline, stdout);
                            send(newsockfd, sendline, MAX_BUFFER_SIZE, 0);
                            products[i].qty -= new_qty;
                            break;
                        }
                    }

                    // wait for client option (continue to buy or end communication)
                    memset(recline, 0, MAX_BUFFER_SIZE);
                    printf("witing for continue or end communication\n");
                    received_bytes = recv(newsockfd, recline, MAX_BUFFER_SIZE, 0);
                    recline[received_bytes-2] = 0;
                    printf("client pressed %c\n", recline[0]);
                    if(recline[0] != 'c') {
                        return -1;
                    } 
                }
            }
        } else {
            close(newsockfd);
        }
    }

    close(sockfd);

    return 0;
}