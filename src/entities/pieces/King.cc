#include "King.h"
#include "Rook.h"
#include "../Board.h"
#include "../Piece.h"

King::King(Colour colour) : Piece{colour} {}

King::King(const King& other) : Piece{other} {}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this);
}

const char King::getType() const { 
    return 'k'; 
}

bool King::isValidMove(const Board& board, int startRow, int startCol, int endRow, int endCol) const {
    if (startRow == endRow && startCol == endCol) {
        return false;
    }

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
            std::shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(rookTile->getPiece());
            if (rook && rookTile->getPiece()->getType() == 'r') {
                if (!rook->hasMoved() && board.getTile(startRow, 5)->isEmpty() && board.getTile(startRow, 6)->isEmpty()) {
                    // Simulate the king's intermediate move
                    shared_ptr<Board> tempboard = make_shared<Board>(board);
                    tempboard->movePiece(startRow, startCol, startRow, startCol + 1);
                    if (isInCheck(*tempboard, startRow, startCol + 1)) {
                        return false;
                    }

                    return true;
                }
            }
        } else if (endCol == startCol - 2) {
            // Queenside castling
            std::shared_ptr<Tile> rookTile = board.getTile(startRow, 0);
            std::shared_ptr<Rook> rook = dynamic_pointer_cast<Rook>(rookTile->getPiece());
            if (rook && rookTile->getPiece()->getType() == 'r') {
                if (!rook->hasMoved() && board.getTile(startRow, 1)->isEmpty() && board.getTile(startRow, 2)->isEmpty() && board.getTile(startRow, 3)->isEmpty()) {
                    
                    // Simulate the king's intermediate move
                    shared_ptr<Board> tempboard = make_shared<Board>(board);
                    tempboard->movePiece(startRow, startCol, startRow, startCol - 1);
                    if (isInCheck(*tempboard, startRow, startCol - 1)) {
                        return false;
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

bool King::isInCheck(const Board& board, int kingRow, int kingCol) const {
    Colour opponentColour = (getColour() == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

    // check all enemy pieces if they are attacking the king position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board.getTile(row, col)->getPiece();
            // Check if the piece is an opponent's piece (cannot be a the enemy king putting the king in check either)
            if (piece && piece->getColour() == opponentColour) {
                // Check if this piece can move to the king's position
                if (piece->isValidMove(board, row, col, kingRow, kingCol)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}
