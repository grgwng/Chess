#ifndef MOVE_H
#define MOVE_H

#include "../types/types.h"

struct Move {
    Colour player;
    char pieceType;
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    Move(Colour p, char pieceType, int sr, int sc, int er, int ec)
        : player{p}, pieceType{pieceType}, startRow{sr}, startCol{sc}, endRow{er}, endCol{ec} {}
};

#endif // MOVE_H