#include "Tile.h"
#include <memory>

Tile::Tile(int row, int col, Colour colour): row{row}, col{col}, colour{colour}, p{nullptr} {}

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

