#ifndef GAME_H
#define GAME_H

#include <Board.h>
#include <vector>

#include "Move.h"

using namespace std;

class Game {
    std::shared_ptr<Board> board;
    vector<Move> moveHistory;
public:
    Game();
    void makeMove();

    bool checkCheck(Colour colour);
    bool checkCheckmate(Colour colour);
    bool checkStalemate(Colour colour);
    bool checkPromotion(Colour colour);

    bool checkDraw();

    void resign();

    ~Game();
};

#endif