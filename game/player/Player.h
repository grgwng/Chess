#ifndef PLAYER_H
#define PLAYER_H

#include "../../types/types.h"
#include "../../interpreter/Interpreter.h"
#include "../Move.h"
#include "../../entities/Board.h"

class Player {
    protected:
        Colour colour;
public:
    Player(Colour colour);
    virtual Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board) = 0;
    virtual ~Player() {};
};

#endif
