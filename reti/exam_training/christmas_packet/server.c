#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1000
#define MAX_MESSAGES_N 500
#define MAX_MESSAGE_TEXT 200

typedef struct Message {
    char text[MAX_MESSAGE_TEXT];
    struct sockaddr_in client;
} Message;

char *getActionList() {
    return "0 - Save a new message\n1 - View all sent messages\n2 - Edit a message\n3 - Delete a message\n";
}

short int insertMessage(Message messages[], int *messages_n, struct sockaddr_in client, char *new_msg) {
    short int inserted = -1;
    for(int i = 0; i < (*messages_n)+1; i++) {
        if(messages[i].client.sin_port == 0) {
            strcpy(messages[i].text, new_msg);
            messages[i].client = client;
            inserted = 0;
            (*messages_n)++;
            break;
        }
    }
    return inserted;
}

short int editMessage(Message messages[], int messages_n, struct sockaddr_in client, int msg_index, char *new_msg) {
    short int updated = -1;
    for(int i = 0; i < messages_n; i++) {
        if(i == msg_index-1 && messages[i].client.sin_port == client.sin_port && messages[i].client.sin_addr.s_addr == client.sin_addr.s_addr) {
            strcpy(messages[i].text, new_msg);
            updated = 0;
            break;
        }
    }
    return updated;
}

short int deleteMessage(Message messages[], int messages_n, struct sockaddr_in client, int msg_index) {
    short int deleted = -1;
    Message tmp[MAX_MESSAGES_N];
    int tmp_i = 0;
    for(int i = 0; i < messages_n; i++) {
        if(i == msg_index-1 && messages[i].client.sin_port == client.sin_port && messages[i].client.sin_addr.s_addr == client.sin_addr.s_addr) {
            deleted = 0;
        } else {
            tmp[tmp_i].client = messages[i].client;
            strcpy(tmp[tmp_i].text, messages[i].text);
            tmp_i++;
        }
    }
    for(int i = 0; i < messages_n; i++) {
        messages[i].client = tmp[i].client;
        strcpy(messages[i].text, tmp[i].text);
    }
    return deleted;
}

char *getMessages(Message messages[], int messages_n, struct sockaddr_in client) {
    char *res = malloc(MAX_BUFFER_SIZE);
    if (res == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    for(int i = 0; i < messages_n; i++) {
        if(messages[i].client.sin_addr.s_addr == client.sin_addr.s_addr && messages[i].client.sin_port == client.sin_port) {
            char tmp[50];
            sprintf(tmp, "Message %d:\n", i+1);
            strcat(res, tmp);
            strcat(res, messages[i].text);
            strcat(res, "\n");
        }
    }
    return res;
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char msg[MAX_BUFFER_SIZE];
    int received_bytes = 0;
    Message messages[MAX_MESSAGES_N];
    int messages_n = 0;

    if(argc != 2) {
        printf("Error. Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error occurred while opening socket\n");
        return -1;
    }

    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        printf("Error. Please insert a different port number\n");
        return -1;
    }

    received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
    msg[received_bytes] = 0;
    for(;;) {
        // send actions list
        sendto(sockfd, getActionList(), MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
        // receive selected action
        received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
        msg[received_bytes] = 0;
        // Save a new message
        if(msg[0] == '0') {
            received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            msg[received_bytes] = 0;
            if(insertMessage(messages, &messages_n, remote_addr, msg) == 0) sendto(sockfd, "The new message has been saved correctly\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
            else sendto(sockfd, "An error occurred while creating a new message\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
        }
        // View all messages
        else if(msg[0] == '1') {
            char *msglist = getMessages(messages, messages_n, remote_addr);
            sendto(sockfd, msglist, strlen(msglist), 0, (struct sockaddr *)&remote_addr, len);
        } 
        // Edit a message
        else if(msg[0] == '2') {
            received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            msg[received_bytes] = 0;
            int msg_index = atoi(msg);
            received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            msg[received_bytes] = 0;
            if(editMessage(messages, messages_n, remote_addr, msg_index, msg) == 0) sendto(sockfd, "The message has been updated correctly\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
            else sendto(sockfd, "An error occurred while updating the message\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
        } 
        // Delete a messages
        else if(msg[0] == '3') {
            received_bytes = recvfrom(sockfd, msg, MAX_BUFFER_SIZE-1, 0, (struct sockaddr *)&remote_addr, &len);
            msg[received_bytes] = 0;
            int msg_index = atoi(msg);
            if(deleteMessage(messages, messages_n, remote_addr, msg_index) == 0) sendto(sockfd, "The message has been deleted correctly\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
            else sendto(sockfd, "An error occurred while deleting the message\n", MAX_BUFFER_SIZE, 0, (struct sockaddr *)&remote_addr, len);
        }
        // end communication
        else if(msg[0] == 'q') {
            printf("Client %s:%d has ended communication\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
            fflush(stdout);
        }
    }

    printf("End of comnunication\n");
    fflush(stdout);
    close(sockfd);

    return 0;
}