#ifndef MOVE_H
#define MOVE_H

#include "../types/types.h"

struct Move {
    Colour player;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    char promotionType;
    bool isResign;

    Move(Colour p, int sr, int sc, int er, int ec, char promotionType, bool isResign)
        : player{p}, startRow{sr}, startCol{sc}, endRow{er}, endCol{ec}, promotionType{promotionType}, isResign{isResign}{}

};

Move invalidMove();

Move resignMove(Colour c);

#endif