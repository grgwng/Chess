#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece {
public:
    Pawn(Colour colour) : Piece(colour) {}

    const char getType() const override { return 'p'; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

#endif