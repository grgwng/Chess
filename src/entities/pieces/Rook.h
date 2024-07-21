#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"

class Rook : public Piece {
public:
    Rook(Colour colour) : Piece(colour) {}

    const char getType() const override { return "Rook"; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

#endif