#ifndef GRANDMASTER_H
#define GRANDMASTER_H

#include "../Computer.h"

class Grandmaster : public Computer {
    int minimax(const shared_ptr<Board>& board, int depth, bool maximizingPlayer, int alpha, int beta);
    int evaluateBoard(const shared_ptr<Board>& board);
    static const int MAX_DEPTH = 3;
public:
    Grandmaster(Colour colour);
    Move computeMove(const shared_ptr<Board>& board) override;
};

#endif
