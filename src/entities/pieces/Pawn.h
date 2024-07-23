#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"
#include "../Board.h"

class Pawn : public Piece {
private:
    bool enPassantEligible;
public:
    Pawn(Colour colour) : Piece(colour) {}

    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;

    bool isEnPassantEligible() const { return enPassantEligible; }
    void setEnPassantEligible(bool eligible) { enPassantEligible = eligible; }
};

#endif