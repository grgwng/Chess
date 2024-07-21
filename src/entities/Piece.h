#ifndef PIECE_H
#define PIECE_H

#include "Colour.h"

class Piece {
    Colour colour;
public:
    Piece(Colour colour);
    Colour getColour() const;
    virtual const char getType() const = 0;
    virtual bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const = 0;
};

#endif