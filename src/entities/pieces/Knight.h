#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Board.h"

class Knight : public Piece {
public:
    Knight(Colour colour);
    Knight(const Knight& other);
    std::shared_ptr<Piece> clone() const override;
    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif
