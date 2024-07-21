#ifndef PLAYER_H
#define PLAYER_H

#include "../types/types.h"

class Player {
    Colour colour;
public:
    virtual void makeMove() = 0;
    virtual ~Player() {};
};

#endif