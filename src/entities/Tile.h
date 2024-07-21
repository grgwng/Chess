#ifndef TILE_H
#define TILE_H
#include "Piece.h"

class Tile {
    int row, col;
public:
    Piece getPiece();
};

#endif