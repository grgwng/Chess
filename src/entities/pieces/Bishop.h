#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"

class Bishop : public Piece {
public:
    Bishop(Colour colour) : Piece(colour) {}

    const char* getType() const override { return "Bishop"; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

#endif