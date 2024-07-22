#ifndef PIECE_H
#define PIECE_H

#include "../types/types.h"

class Board;
class Tile;

class Piece {
    Colour colour;
    bool hasMovedFlag;
public:
    Piece(Colour colour);
    Colour getColour() const;
    virtual const char getType() const = 0;
    virtual bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const = 0;

    bool hasMoved() const;
    void setHasMoved(bool moved);

    virtual ~Piece() {}
};

#endif