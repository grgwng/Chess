#ifndef PLAYER_H
#define PLAYER_H

#include "../../types/types.h"
#include "../../interpreter/interpreter.h"
#include "../Move.h"
#include "../../entities/Board.h"

class Player {
    protected:
        Colour colour;
public:
    virtual Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board) = 0;
    virtual ~Player() {};
};

#endif