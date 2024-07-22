#include "Queen.h"
#include "../Board.h"
#include "Rook.h"
#include "Bishop.h"

const char Queen::getType() const { 
    return 'q'; 
}

bool Queen::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    // queen is a combination of rook and bishop rules
    if (startRow == endRow || startCol == endCol) {
        return Rook(getColour()).isValidMove(board, startRow, startCol, endRow, endCol);
    } else if (abs(startRow - endRow) == abs(startCol - endCol)) {
        return Bishop(getColour()).isValidMove(board, startRow, startCol, endRow, endCol);
    }
    return false;
}