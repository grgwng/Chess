#ifndef TILE_H
#define TILE_H
#include "Piece.h"

class Piece;

class Tile {
    int row, col;
    Colour colour;
    std::shared_ptr<Piece> p;
public:
    Tile(int row, int col, Colour colour);

    Tile(const Tile& other) : row(other.row), col(other.col), colour(other.colour) {
        if (other.p) {
            p = other.p->clone();
        } else {
            p = nullptr;
        }
    }

    Colour getColour() const;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> piece);
    int getRow() const;
    int getCol() const;
    ~Tile() {}

    bool isEmpty();
};

#endif