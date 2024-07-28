#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 10000

typedef struct Item {
    char company[100];
    size_t id;
    char name[100];
    unsigned int qty;
    float price;
} Item;

size_t senddata(int sockfd, char *str) {
    return send(sockfd, str, strlen(str), 0);
}

int main(int argc, char **argv) {
    int sockfd, newsockfd, received_bytes = 0;
    struct sockaddr_in6 local_addr, remote_addr;
    socklen_t s_len = sizeof(struct sockaddr_in6);
    char msg[MAX_BUFFER_SIZE];
    if(argc != 2) {
        printf("Insert port number\n");
        return -1;
    }
    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
        printf("Error while socket opening\n");
        return -1;
    }

    memset(&local_addr, 0, s_len);
    local_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "0.0.0.0", &local_addr.sin6_addr);
    local_addr.sin6_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, s_len) < 0) {
        printf("Error while binding\n");
        return -1;
    }
    
    listen(sockfd, 5);

    for(;;) {
        newsockfd = accept(sockfd, (struct sockaddr *)&remote_addr, &s_len);
        printf("new connection received\n");
        int pid = fork();
        if(pid == 0) {
            close(sockfd);
            char company_name[100];
            // receive company name required for some operations
            memset(msg, 0, sizeof(msg));
            received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
            msg[received_bytes] = 0;
            strcpy(company_name, msg);

            for(;;) {
                senddata(newsockfd, "0 - List all of your registered products\n1 - Register a new product\n2 - Edit a product\n3 - End connection\n");
                memset(msg, 0, sizeof(msg));
                received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                msg[received_bytes] = 0;
                if(msg[0] == '3') {
                    return 0;
                } else if(msg[0] == '0') {
                    // get total items n
                    FILE *f = fopen("wines.dat", "rb");
                    fseek(f, 0, SEEK_END);
                    size_t total_bytes = ftell(f);
                    fseek(f, 0, SEEK_SET);
                    int total_items = (int)total_bytes/sizeof(Item);
                    Item items[total_items];
                    fread(&items, sizeof(Item), total_items, f);
                    fclose(f);
                    char *res = malloc(300*total_items);
                    for(int i = 0; i < total_items; i++) {
                        if(strcmp(items[i].company,company_name) == 0) {
                            char tmp[200];
                            sprintf(tmp, "Article %d\nID: %ld\nCompany name: %s\nQuantity: %d\nPrice: %.2f\n\n", i+1, items[i].id, items[i].company, items[i].qty, items[i].price);
                            strcat(res, tmp);
                        }
                    }
                    size_t ttt = senddata(newsockfd, res);
                    free(res);
                    // receive confirmation received
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes] = 0;
                } else if(msg[0] == '1') {
                    senddata(newsockfd, "Insert a new product like <name>;<quantity>;<price>\n");
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes-1] = 0; // remove \n

                    // fetch last registered prod id
                    Item last_item;
                    FILE *f = fopen("wines.dat", "rb");
                    fseek(f, 0, SEEK_END);
                    fseek(f, -sizeof(last_item), SEEK_CUR);
                    fread(&last_item, sizeof(last_item), 1, f);
                    fclose(f);

                    // register new product
                    Item new_item;
                    strcpy(new_item.company, company_name);
                    char *part = strtok(msg, ";");
                    strcpy(new_item.name, part);
                    part = strtok(NULL, ";");
                    new_item.qty = atoi(part);
                    part = strtok(NULL, ";");
                    new_item.price = atof(part);
                    new_item.id = last_item.id+1;
                    f = fopen("wines.dat", "ab");
                    if(f == NULL) perror("Error occurred while opening file\n");
                    int n = fwrite(&new_item, sizeof(new_item), 1, f);
                    if(n > 0) senddata(newsockfd, "Product registered correctly\n");
                    else senddata(newsockfd, "Error while registering new product\n");
                    fclose(f);
                } else if(msg[0] == '2') {
                    senddata(newsockfd, "Please, insert the id of the item to update e the new quantity like <item_id>;<new_qty>\n");
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes] = 0;
                    char *part = strtok(msg, ";");
                    size_t id_to_update = atoi(part);
                    part = strtok(NULL, ";");
                    int new_qty = atoi(part);
                    Item toUpdate;
                    FILE *f = fopen("wines.dat", "rb+");
                    fseek(f, 0, SEEK_SET);
                    short int found = -1;
                    while (fread(&toUpdate, sizeof(Item), 1, f) > 0) {
                        if(toUpdate.id == id_to_update) {
                            fseek(f, -sizeof(Item), SEEK_CUR);
                            toUpdate.qty = new_qty;
                            fwrite(&toUpdate, sizeof(Item), 1, f);
                            found = 1;
                            break;
                        }
                    }
                    fclose(f);
                    if(found == -1) senddata(newsockfd, "Item was not found\n");
                    else senddata(newsockfd, "Item updated successfully\n");
                    // receive confirmation received
                    memset(msg, 0, sizeof(msg));
                    received_bytes = recv(newsockfd, msg, MAX_BUFFER_SIZE-1, 0);
                    msg[received_bytes] = 0;
                }
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            char ip_addr[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &remote_addr.sin6_addr, ip_addr, INET6_ADDRSTRLEN);
            printf("Connection with client %s:%d close\n", ip_addr, ntohs(remote_addr.sin6_port));
            close(newsockfd);
        }
    }

    close(sockfd);

    return 0;
}