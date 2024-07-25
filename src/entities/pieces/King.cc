#include "King.h"
#include "Rook.h"
#include "../Board.h"
#include "../Piece.h"

King::King(Colour colour) : Piece{colour} {}

const char King::getType() const { 
    return 'k'; 
}

bool King::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    if (abs(endCol - startCol) <= 1 && abs(endRow - startRow) <= 1) {
        // check there is not a piece of same colour at the end position
        const std::shared_ptr<Piece> targetPiece = board.getTile(endRow, endCol)->getPiece();
        if (targetPiece && targetPiece->getColour() == getColour()) {
            return false; 
        }
        return true;
    }

    // Castling
    if (canCastle() && startRow == endRow) {
        if (endCol == startCol + 2) {
            // Kingside castling
            std::shared_ptr<Tile> rookTile = board.getTile(startRow, 7);
            if (rookTile->getPiece()->getType() == 'r') {
                std::shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(rookTile->getPiece());
                if (!rook->hasMoved() && board.getTile(startRow, 5)->isEmpty() && board.getTile(startRow, 6)->isEmpty()) {
                    return true;
                }
            }
        } else if (endCol == startCol - 2) {
            // Queenside castling
            std::shared_ptr<Tile> rookTile = board.getTile(startRow, 0);
            if (rookTile->getPiece()->getType() == 'r') {
                std::shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(rookTile->getPiece());
                if (!rook->hasMoved() && board.getTile(startRow, 1)->isEmpty() && board.getTile(startRow, 2)->isEmpty() && board.getTile(startRow, 3)->isEmpty()) {
                    return true;
                }
            }
        }
    }

    return false;
}