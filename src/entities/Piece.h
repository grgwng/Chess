#ifndef PIECE_H
#define PIECE_H

#include "types.h"

class Piece {
    Colour colour;
    bool hasMovedFlag;
public:
    Piece(Colour colour);
    Colour getColour() const;
    virtual const char getType() const = 0;
    virtual bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const = 0;

    bool hasMoved() const;
    void setHasMoved(bool moved);
};

#endif