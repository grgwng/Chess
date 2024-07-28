#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class Computer : public Player {
public:
    Computer(Colour colour);
    virtual Move computeMove(const shared_ptr<Board>& board) = 0;
    Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board);
};

#endif