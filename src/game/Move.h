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
        : player{p}, promotionType{promotionType}, startRow{sr}, startCol{sc}, endRow{er}, endCol{ec} {}

};

Move invalidMove();

Move resignMove(Colour c);

#endif // MOVE_H