#include "Piece.h"

Piece::Piece(Colour colour) : colour(colour), hasMovedFlag(false) {}

Colour Piece::getColour() const { return colour;};

bool Piece::hasMoved() const { return hasMovedFlag; }

void Piece::setHasMoved(bool moved) { hasMovedFlag = moved; }