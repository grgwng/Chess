#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"
#include "../Board.h"

class Rook : public Piece {
public:
    Rook(Colour colour) : Piece(colour) {}

    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif