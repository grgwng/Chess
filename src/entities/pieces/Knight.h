#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Board.h"

class Knight : public Piece {
public:
    Knight(Colour colour) : Piece(colour) {}

    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif