#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"
#include "../Board.h"

class Queen : public Piece {
public:
    Queen(Colour colour);

    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif