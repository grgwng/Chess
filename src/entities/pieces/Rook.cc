#include "Rook.h"
#include "Board.h"

bool Rook::isValidMove(const Board& board, int startX, int startY, int endX, int endY) const {
    return abs(startX - endX) <= 1 && abs(startY - endY) <= 1;
}