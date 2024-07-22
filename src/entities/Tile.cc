#include "Tile.h"
#include <memory>

Tile::Tile(int row, int col, Colour colour): colour{colour}, p{nullptr} {}

Colour Tile::getColour() const {
    return colour;
}

std::shared_ptr<Piece> Tile::getPiece() const {
    return p;
}

void Tile::setPiece(std::shared_ptr<Piece> piece) {
    p = piece;
} 

bool Tile::isEmpty() {
    return p == nullptr;
}

