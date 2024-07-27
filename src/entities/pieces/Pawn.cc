#include "Pawn.h"
#include "../Board.h"
#include "../../types/types.h"

Pawn::Pawn(Colour colour) : Piece{colour}, enPassantEligible{false} {}

const char Pawn::getType() const { 
    return 'p'; 
}

bool Pawn::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    if (startRow == endRow && startCol == endCol) {
        return false;
    }

    // White pawns move up, black pawns move down
    int direction = (getColour() == Colour::WHITE) ? -1 : 1; // white moving up, black moving down

    if (startCol == endCol) { // must be moving vertically
        // single move to empty space
        if (endRow == startRow + direction && board.getTile(endRow, endCol)->isEmpty()) {
            return true;
        }

        // two spaces move is valid on first move
        if ((startRow == 6 && getColour() == Colour::WHITE) || (startRow == 1 && getColour() == Colour::BLACK)) {
            // check if seeking to move 2 spaces, then check if both spaces ahead are empty
            if (endRow == startRow + (2 * direction) && board.getTile(endRow, endCol)->isEmpty() && board.getTile(startRow + direction, startCol)->isEmpty()) {
                return true;
            }
        }
    } else if (abs(startCol - endCol) == 1 && endRow == startRow + direction) { // must be moving diagonally in the correct direction for capture
        const std::shared_ptr<Piece> targetPiece = board.getTile(endRow, endCol)->getPiece();
        if (targetPiece && targetPiece->getColour() != getColour()) {
            return true; // Capturing opponent's piece
        } else if (!targetPiece && board.getTile(startRow, endCol)->getPiece() &&
                   board.getTile(startRow, endCol)->getPiece()->getType() == 'p' &&
                   dynamic_pointer_cast<Pawn>(board.getTile(startRow, endCol)->getPiece())->isEnPassantEligible()) {
            return true; // En passant capture
        }
    }

    return false;
}