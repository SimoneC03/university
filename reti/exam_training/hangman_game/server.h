
typedef struct {
    char name[MAX_PLAYER_NAME];
    in_addr_t ip;
    in_port_t port;
    int chances;
} Client;

short int isGameEnd(Client players[]);
char *getRandomWord();
ssize_t sendLine(int sockfd, char *mes, struct sockaddr_in dest_addr);
int getPlayerIndex(in_addr_t ip, in_port_t port, Client players[]);
char *canJoin(in_addr_t ip, char *name, in_port_t port, Client players[]);
char *getWordStructure(char *word, char chars[]);