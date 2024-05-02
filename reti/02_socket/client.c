#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    // destination address
    struct sockaddr_in dest_addr;
    // text buffer to send to server
    char buffer[100];
    // socket descriptor
    int sockfd;

    if(argc < 3) {
        printf("Please insert destination IP and port\n");
        return -1;
    }
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("An error has occurred while socket opening\n");
        return -1;
    }

    // set all bytes to 0
    memset(&dest_addr, 0, sizeof(dest_addr));
    // IPv4 address family
    dest_addr.sin_family = AF_INET;
    // convert address to binary network format
    inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr));
    // convert the port number from host byte order to network byte order
    dest_addr.sin_port = htons(atoi(argv[2]));

    for(int i = 0; i < 10; i++) {
        sprintf(buffer, "%d", i);
        // send current buffer to destination address
        sendto(sockfd, buffer, sizeof(buffer)+1, 0, (struct sockaddr_in *)&dest_addr, sizeof(dest_addr));
    }

    // close the socket connection
    close(sockfd);
    return 0;
}