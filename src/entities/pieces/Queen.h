#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"
#include "../Board.h"

class Queen : public Piece {
public:
    Queen(Colour colour);
    Queen(const Queen& other);
    std::shared_ptr<Piece> clone() const override;
    
    const char getType() const override;
    bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const override;
};

#endif