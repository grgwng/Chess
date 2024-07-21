#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Board.h"

class Knight : public Piece {
public:
    Knight(Colour colour) : Piece(colour) {}

    const char getType() const override { return 'n'; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

#endif