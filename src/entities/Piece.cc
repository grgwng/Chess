#include "Piece.h"
#include <memory>

Piece::Piece(Colour colour) : colour{colour}, hasMovedFlag{false} {}

Piece::Piece(const Piece& other) : colour{other.colour}, hasMovedFlag{other.hasMovedFlag} {}

Colour Piece::getColour() const { return colour;};

bool Piece::hasMoved() const { return hasMovedFlag; }

void Piece::setHasMoved(bool moved) { hasMovedFlag = moved; }
