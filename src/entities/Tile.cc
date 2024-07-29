#include "Tile.h"
#include <memory>
#include <iostream>

Tile::Tile(int row, int col, Colour colour): row{row}, col{col}, colour{colour}, p{nullptr} {}

Tile::Tile(const Tile& other) : row{other.row}, col{other.col}, colour{other.colour} {
    if (other.p) {
        p = other.p->clone();
    } else {
        p = nullptr;
    }
}

Colour Tile::getColour() const {
    return colour;
}

std::shared_ptr<Piece> Tile::getPiece() const {
    return p;
}

void Tile::setPiece(std::shared_ptr<Piece> piece) {
    p = piece;
} 

int Tile::getRow() const { 
    return row; 
};

int Tile::getCol() const { 
    return col;
};

bool Tile::isEmpty() {
    return p == nullptr;
}
