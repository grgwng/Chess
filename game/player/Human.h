#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
    Move convertMoveCommandToMove(shared_ptr<MoveCommand> mc);
public:
    Human(Colour colour);
    virtual Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board) override;
};

#endif
