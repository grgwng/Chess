#ifndef TILE_H
#define TILE_H
#include "Piece.h"

class Piece;

class Tile {
    int row, col;
    Colour colour;
    Piece* p;
public:
    Tile(int row, int col, Colour colour);
    Colour getColour() const;
    Piece* getPiece();
    void setPiece(Piece* p);
    ~Tile() {}

    bool isEmpty();
};

#endif