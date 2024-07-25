#include "Bishop.h"
#include "../Board.h"

Bishop::Bishop(Colour colour) : Piece{colour} {}

const char Bishop::getType() const { 
    return 'b'; 
}

bool Bishop::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    // must be a diagonal move
    if (abs(startRow - endRow) != abs(startCol - endCol)) {
        return false;
    }


    // check there are no pieces in the way towards the end position
    int rowDirection = (endRow - startRow) > 0 ? 1 : -1;
    int colDirection = (endCol - startCol) > 0 ? 1 : -1;
    for (int currRow = startRow + rowDirection, currCol = startCol + colDirection; 
        currRow != endRow && currCol != endCol; 
        currRow += rowDirection, currCol += colDirection) {
            
        if (!board.getTile(currRow, currCol)->isEmpty()) {
            return false;
        }
    }

    // check there is not a piece of same colour at the end position
    const std::shared_ptr<Piece> targetPiece = board.getTile(endRow, endCol)->getPiece();
    if (targetPiece && targetPiece->getColour() == getColour()) {
        return false;
    }

    return true;
}