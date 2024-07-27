#include "Game.h"


Game::Game() {}

void Game::makeMove() {

}

bool Game::checkCheck(Colour colour) {
    Colour opponentColour = (colour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());
    return king->isInCheck(*board, kingTile->getRow(), kingTile->getCol());
}

bool Game::checkCheckmate(Colour colour) {
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());

    if (!king->isInCheck(*board, kingTile->getRow(), kingTile->getCol())) {
        return false;
    }

    // king must be in check now
    // Check if there is any legal move for the king to escape check. Iterate through all possible moves for the king
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            int newRow = kingTile->getRow() + rowOffset;
            int newCol = kingTile->getCol() + colOffset;
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (king->isValidMove(*board, kingTile->getRow(), kingTile->getCol(), newRow, newCol)) {
                    return true; // king has a valid move so can escape check
                }
            }
        }
    }

    // Check if there is any legal move for any piece of same colour to block the check or capture the attacking piece
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board->getTile(row, col)->getPiece();
            if (piece && piece->getColour() == colour) {
                for (int endRow = 0; endRow < 8; ++endRow) {
                    for (int endCol = 0; endCol < 8; ++endCol) {
                        if (piece->isValidMove(*board, row, col, endRow, endCol)) {
                            // Simulate the move
                            Board tempBoard = *board; // Make a copy of the board
                            tempBoard.movePiece(row, col, endRow, endCol);

                            // Check if the king is still in check after the move
                            if (!king->isInCheck(tempBoard, kingTile->getRow(), kingTile->getCol())) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true; // King is in checkmate
}


bool Game::checkStalemate(Colour colour) {
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());
    if (king->isInCheck(*board, kingTile->getRow(), kingTile->getCol())) {
        return false;
    }

    // Check if there are any legal moves available for all pieces of a certain colour
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board->getTile(row, col)->getPiece();
            if (piece && piece->getColour() == colour) {
                for (int endRow = 0; endRow < 8; ++endRow) {
                    for (int endCol = 0; endCol < 8; ++endCol) {
                        if (piece->isValidMove(*board, row, col, endRow, endCol)) {
                            return false; // Found a valid move so not stalemate
                        }
                    }
                }
            }
        }
    }

    return true; // No valid moves found
}

bool Game::checkPromotion(Colour colour) {

    // once promoted need to check check & checkmate conditions again
}

bool Game::checkDraw() {

}

void Game::resign() {

}