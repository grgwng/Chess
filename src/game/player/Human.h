#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
public:
    Human();
    virtual Move makeMove(const unique_ptr<Interpreter> interpreter, const shared_ptr<Board> board) override;
};

#endif