# Hangman game
## Description
Two clients will compete to guess a secret word located in the server machine. Every player (client) has three chances managed by the server.
For each turn:
- The server sends to the player whose turn it is to play the state of the game (like guessed or missing letters).
- In turn, each player can write a single letter or the entire word. If it's wrong it will lose a chance.
- If a player lose all his chances, it will exit and lose the game.
## Some constraints
- The server will have to store the player's name, IP address and port in a client `struct Client`.
- Maximum only 2 clients can play per game and the game will only start when the server will have registered the two players.
- The server will randomly choose a string to use for the game among those present in a two-dimensional array.