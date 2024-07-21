#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"

class Queen : public Piece {
public:
    Queen(Colour colour) : Piece(colour) {}

    const char* getType() const override { return "Queen"; }
    bool isValidMove(const Board& board, int startX, int startY, int endX, int endY) const override;
};

#endif