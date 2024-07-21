#include "King.h"
#include "Rook.h"
#include "../Board.h"
#include "../Piece.h"

bool King::isValidMove(const Board& board, int startX, int startY, int endX, int endY) const {
    if (abs(startX - endX) <= 1 && abs(startY - endY) <= 1) {
        const Piece* targetPiece = board.getTile(endX, endY)->getPiece();
        if (!board.getTile(endX, endY)->isEmpty() && targetPiece->getColour() == getColour()) {
            return false; // Cannot move to a tile occupied by a piece of the same colour
        }
        return true;
    }

    // Castling
    if (startY == endY && canCastle()) {
        if (endX == startX + 2) {
            // Kingside castling
            Tile* rookTile = board.getTile(7, startY);
            if (rookTile->getPiece()->getType() == 'r') {
                Rook* rook = dynamic_cast<Rook*>(rookTile->getPiece());
                if (!rook->hasMoved() && board.getTile(5, startY)->isEmpty() && board.getTile(6, startY)->isEmpty()) {
                    return true;
                }
            }
        } else if (endX == startX - 2) {
            // Queenside castling
            Tile* rookTile = board.getTile(0, startY);
            if (rookTile->getPiece()->getType() == 'r') {
                Rook* rook = dynamic_cast<Rook*>(rookTile->getPiece());
                if (!rook->hasMoved() && board.getTile(1, startY)->isEmpty() && board.getTile(2, startY)->isEmpty() && board.getTile(3, startY)->isEmpty()) {
                    return true;
                }
            }

        }
    }

    return false;
}