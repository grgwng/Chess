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

    bool operator<(const Move& other) const {
        if (startRow != other.startRow) return startRow < other.startRow;
        if (startCol != other.startCol) return startCol < other.startCol;
        if (endRow != other.endRow) return endRow < other.endRow;
        if (endCol != other.endCol) return endCol < other.endCol;
        if (promotionType != other.promotionType) return promotionType < other.promotionType;
        return isResign < other.isResign;
    }
};

Move invalidMove();

Move resignMove(Colour c);

Move quitMove();

#endif