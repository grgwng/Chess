#include "Rook.h"
#include "../Board.h"

Rook::Rook(Colour colour) : Piece{colour} {}

Rook::Rook(const Rook& other) : Piece{other} {}

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}

const char Rook::getType() const { 
    return 'r'; 
}

bool Rook::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    if (startRow == endRow && startCol == endCol) {
        return false;
    }

    if (startRow != endRow && startCol != endCol) { // if not moving horizontally or vertically then invalid
        return false;
    }

    if (startCol == endCol) { // moving vertically
        int direction = (endRow - startRow) > 0 ? 1 : -1;
        // return false if something blocking the way towards endRow
        for (int currRow = startRow + direction; currRow != endRow; currRow += direction) {
            if (!board.getTile(currRow, startCol)->isEmpty()) {
                return false;
            }
        }
    } else { // moving horizontally
        int direction = (endCol - startCol) > 0 ? 1 : -1;
        // return false if something blocking the way towards endX
        for (int currCol = startCol + direction; currCol != endCol; currCol += direction) {
            if (!board.getTile(startRow, currCol)->isEmpty()) {
                return false;
            }
        }
    }

    // check there is not a piece of same colour at the end position
    const std::shared_ptr<Piece> targetPiece = board.getTile(endRow, endCol)->getPiece();
    if (targetPiece && targetPiece->getColour() == getColour()) {
        return false; 
    }

    return true;
}