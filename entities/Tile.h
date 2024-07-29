#ifndef TILE_H
#define TILE_H

#include <memory>
#include "Piece.h"

class Tile {
    int row, col;
    Colour colour;
    std::shared_ptr<Piece> p;
public:
    Tile(int row, int col, Colour colour);

    Tile(const Tile& other);

    Colour getColour() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> piece);
    int getRow() const;
    int getCol() const;
    ~Tile() {}

    bool isEmpty();
};

#endif
