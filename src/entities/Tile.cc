#include "Tile.h"

Tile::Tile(int row, int col, Colour colour): row{row}, col{col}, colour{colour}, p{nullptr} {}

Colour Tile::getColour() const {
    return colour;
}

Piece* Tile::getPiece() {
    return p;
}

void Tile::setPiece(Piece *piece) {
    p = piece;
} 

bool Tile::isEmpty() {
    return p == nullptr;
}

