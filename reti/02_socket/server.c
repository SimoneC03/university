#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    // local (server) and remote (incoming requests) addresses
    struct sockaddr_in local_addr, remote_addr;
    // text buffer to send to server
    char buffer[100];
    // socket descriptor
    int sockfd;
    
    socklen_t len = sizeof(struct sockaddr_in);

    if(argc < 2) {
        printf("Please insert port number\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("An error has occurred while socket opening\n");
        return -1;
    }

    // set all bytes to 0
    memset(&local_addr, 0, len);
    // IPv4 address family
    local_addr.sin_family = AF_INET;
    // convert the port number from host byte order to network byte order
    local_addr.sin_port = htons(atoi(argv[1]));

    // try to bind the socket connection to the specified local address and port
    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0) {
        printf("Connection refused. Insert a different port number\n");
        return -1;
    }

    // infinite loop to keep listening for incoming requests
    for(;;) {
        // read and print bytes from incoming socket request
        recvfrom(sockfd, buffer, 99, 0, (struct sockaddr_in *)&remote_addr, len);
        printf("IP = %s, port = %d, MSG = %s\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), buffer);
    }

    // close the socket connection
    close(sockfd);

    return 0;
}