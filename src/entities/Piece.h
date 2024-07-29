#ifndef PIECE_H
#define PIECE_H


#include <vector>
#include "../types/types.h"
#include "../game/Move.h"

class Board;
class Tile;

class Piece {
    Colour colour;
    bool hasMovedFlag;
public:
    Piece(Colour colour);
    Piece(const Piece& other);
    Colour getColour() const;
    virtual const char getType() const = 0;
    virtual bool isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const = 0;

    bool hasMoved() const;
    void setHasMoved(bool moved);
    std::vector<Move> getValidMoves(const Board& board, int startRow, int startCol);

    virtual std::shared_ptr<Piece> clone() const = 0;

    virtual ~Piece() {}
};

#endif
