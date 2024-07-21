#ifndef KING_H
#define KING_H

#include "../Piece.h"
#include "../Board.h"

class King : public Piece {
public:
    King(Colour colour) : Piece(colour) {}

    const char getType() const override { return 'k'; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;

    bool canCastle() const { return !hasMoved(); }
};

#endif