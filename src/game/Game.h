#ifndef GAME_H
#define GAME_H

#include <Board.h>
#include <vector>
using namespace std;

class Game {
    std::shared_ptr<Board> board;
public:
    Game();
    void makeMove();
    ~Game();
};

#endif