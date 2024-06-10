/* This struct represents a Player that has been registered to join the game.
 * It helps to keep track of players information during the game and to 
 * authenticate the incoming requests. */
typedef struct {
    char name[MAX_PLAYER_NAME];
    in_addr_t ip;
    in_port_t port;
    int chances;
} Player;

short int isGameEnd(Player players[]);
char *getRandomWord();
ssize_t sendLine(int sockfd, char *mes, struct sockaddr_in dest_addr);
int getPlayerIndex(in_addr_t ip, in_port_t port, Player players[]);
char *canJoin(in_addr_t ip, char *name, in_port_t port, Player players[]);
char *getWordStructure(char *word, char chars[]);