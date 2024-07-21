#ifndef TILE_H
#define TILE_H
#include "Piece.h"
#include "Colour.h"

class Tile {
    int row, col;
    Colour colour;
    Piece* p;
public:
    Tile(Colour colour);
    Colour getColour();
    Piece* getPiece();
    void setPiece(Piece* p);
};

#endif