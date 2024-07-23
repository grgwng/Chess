#ifndef TILE_H
#define TILE_H
#include "Piece.h"
#include <memory>

class Piece;

class Tile {
    Colour colour;
    std::shared_ptr<Piece> p;
public:
    Tile(int row, int col, Colour colour);
    Colour getColour() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> piece);
    ~Tile() {}

    bool isEmpty();
};

#endif