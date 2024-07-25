#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"
#include "../Board.h"

class Bishop : public Piece {
public:
    Bishop(Colour colour);

    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif