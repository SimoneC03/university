#include <iostream>
#include <string>
#include <vector>

using std::string, std::cout, std::ostream, std::cin, std::isdigit;

bool isNumeric(string);
/* Return whether a string is numeric or not */
bool isNumeric(string str) {
   for (int i = 0; i < str.length(); i++)
      if (isdigit(str[i]) == false)
         return false;
      return true;
}

/* Enum representing all available games */
enum class Game {
    RPS, // Rock-Paper-Scissors
    DiceRoll
};

/* This class represents a registered player that has selected a game to play. */
class Player {
    private:
        string name;
        int score;
        int games; // total games played

    public:
        Player(const string name) : name(name), score(0), games(0) {}
        Player(const string name, const int score, const int games) : name(name), score(score), games(games) {}

        string getName() {
            return name;
        }

        const int getScore() {
            return score;
        }
        
        const int getGames() {
            return games;
        }

        void addScore(const int score) {
            this->score += score;
        }
        
        void addGame() {
            games++;
        }
};

/* This class represents the Rock-Paper-Scissors game with two players
*  required and five rounds to win. */
class RPS {
    public:
        static const int required_players = 2;
        static const int max_players = 2;
        static const int game_score = 5;
        static const short int game_rounds = 5;
        
        static Player *play(Player p1, Player p2) {
            short int i = 0;
            short int p1_won_rounds = 0;
            short int p2_won_rounds = 0;
            Player *winner;
            while(i < game_rounds) {
                i++;
                cout << "\n" << p1.getName() << "'s won rounds: " << p1_won_rounds << "\n";
                cout << p2.getName() << "'s won rounds: " << p2_won_rounds << "\n";
                cout << "-- Round " << i << " --\n";
                cout << p1.getName() << "'s turn: choose between rock, paper and scissors\n";
                string p1_answer;
                cin >> p1_answer;
                cout << p2.getName() << "'s turn: choose between rock, paper and scissors\n";
                string p2_answer;
                cin >> p2_answer;
                if (
                    (p1_answer.compare("paper") == 0 && p2_answer.compare("scissors") == 0) ||
                    (p1_answer.compare("scissors") == 0 && p2_answer.compare("rock") == 0) ||
                    (p1_answer.compare("rock") == 0 && p2_answer.compare("paper") == 0)
                ) {
                    p2_won_rounds++;
                } else if (
                    (p2_answer.compare("paper") == 0 && p1_answer.compare("scissors") == 0) ||
                    (p2_answer.compare("scissors") == 0 && p1_answer.compare("rock") == 0) ||
                    (p2_answer.compare("rock") == 0 && p1_answer.compare("paper") == 0)
                ) {
                    p1_won_rounds++;
                }
            }
            if(p1_won_rounds > p2_won_rounds) {
                /* Player 1 win */
                winner = new Player(p1.getName(), p1.getScore()+game_score, p1.getGames()+1);
                return winner;
            } else if(p2_won_rounds > p1_won_rounds) {
                /* Player 2 win */
                winner = new Player(p2.getName(), p2.getScore()+game_score, p2.getGames()+1);
                return winner;
            } else {
                /* Draw */
                return nullptr;
            }
        }
};

/* This class represents a dice roll game where at least two players
*  are required. Whoever gets the highest score wins */
class DiceRoll {

};

class GameRoom {
    private:
        std::vector<Player> players;
        std::vector<DiceRoll> games;

    public:
        GameRoom() {
            cout << "Welcome!\n";
            askForChoice();
        }

        void printWinner(Player *winner) {
            cout << "\n-------------------------------------------------\n";
            cout << "The winner is " << winner->getName() << "! \n";
            cout << "-------------------------------------------------\n";
        }

        void printLeaderboard() {
            if(players.size() == 0) {
                cout << "\nThere are no registered players at the moment\n";
            } else {
                cout << "\nCurrent leaderboard:\n";
                for(Player p: players) {
                    cout << "- " << p.getName() << " (" << p.getScore() << " points)\n";
                }
                cout << "\n";
            }
        }

        /* Update players stats after a completed match. If a Draw has occurred 
        *  only the Player's total games will be updated. */
        bool updatePlayer(const string &name, const int new_score, const int new_games) {
            bool updated = false;
            for(int i = 0; i < players.size(); i++) {
                if(players[i].getName().compare(name) == 0) {
                    Player p(name, new_score, new_games);
                    players[i] = p;
                    updated = true;
                }
            }
            return updated;
        }

        Player *play(const Game game) {
            if(game == Game::RPS) {
                string p1_, p2_;
                cout << "Insert the name of the player n1: \n";
                cin >> p1_;
                cout << "Insert the name of the player n2: \n";
                cin >> p2_;
                Player p1(p1_), p2(p2_);
                bool p1_found = false;
                bool p2_found = false;
                for(Player &p : players) {
                    if(p.getName().compare(p1_) == 0) {
                        p1 = p;
                        p1_found = true;
                    } else if(p.getName().compare(p2_) == 0) {
                        p2 = p;
                        p2_found;
                    }
                }
                if(!p1_found) players.push_back(p1);
                if(!p2_found) players.push_back(p2);
                RPS rps;
                Player *winner = rps.play(p1, p2);
                if(winner != nullptr) {
                    updatePlayer(winner->getName(), winner->getScore(), winner->getGames());
                } else {
                    /* Draw has occurred, updating only players's total games */
                    updatePlayer(p1.getName(), p1.getScore(), p1.getGames()+1);
                    updatePlayer(p2.getName(), p2.getScore(), p2.getGames()+1);
                }
                return winner;
            } else if(game == Game::DiceRoll) {
                return nullptr;
            } else {
                return nullptr;
            }
        }

        /* Ask the user to choose a game to play with */
        void askForChoice() {
            cout << "\nSelect a game to play with.\n";
            cout << "1 - Rock-Paper-Scissors (2 players required)\n";
            cout << "2 - Dice roll (Min. 2 players required)\n";
            cout << "\n\n8 - Watch leaderboard\n";
            string choice;
            cin >> choice;
            if(isNumeric(choice)) {
                int c = std::stoi(choice);
                switch(c) {
                    /* Rock-Paper-Scissors */
                    case 1: {
                        Player *winner = play(Game::RPS);
                        if(winner != nullptr) printWinner(winner);
                        else cout << "Draw\n";
                        break;
                    }
                    /* Dice roll */
                    case 2: {
                        Player *winner = play(Game::DiceRoll);
                        if(winner != nullptr) printWinner(winner);
                        else cout << "Draw\n";
                        break;
                    }
                    /* Show leaderboard */
                    case 8: {
                        printLeaderboard();
                        askForChoice();
                        break;
                    }
                    default: {
                        cout << "Invalid option.\n";
                        askForChoice();
                    }
                }
                askForChoice();
            } else {
                cout << "Invalid option.\n";
                askForChoice();
            }
        }
};

int main() {
    GameRoom *r = new GameRoom();
    return 0;
}