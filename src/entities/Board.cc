#include "Board.h"
#include "../types/types.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Board::Board() {

    board.resize(boardSize, vector<std::shared_ptr<Tile>>(boardSize, nullptr));
    gameStatus = NOSTATUS;

    for(int row = 0; row < boardSize; row++) {
        for(int col = 0; col < boardSize; col++) {
            Colour curColour = WHITE;

            if(row % 2 == 0) {
                if(col % 2 == 0) {
                    curColour = WHITE;
                }
                else {
                    curColour = BLACK;
                }
            }
            else {
                if(col % 2 == 0) {
                    curColour = BLACK;
                }
                else {
                    curColour = WHITE;
                }
            }

            std::shared_ptr<Tile> newTile = std::make_shared<Tile>(row, col, curColour);

            board[row][col] = newTile;
        }
    }

    // Set up default pieces
    
    // Pawns
    for(int col = 0; col < boardSize; col++) {
        board[1][col]->setPiece(std::make_shared<Pawn>(BLACK));
        board[6][col]->setPiece(std::make_shared<Pawn>(WHITE));
    }

    // Rooks
    board[0][0]->setPiece(std::make_shared<Rook>(BLACK));
    board[0][7]->setPiece(std::make_shared<Rook>(BLACK));
    board[7][0]->setPiece(std::make_shared<Rook>(WHITE));
    board[7][7]->setPiece(std::make_shared<Rook>(WHITE));

    // Knights
    board[0][1]->setPiece(std::make_shared<Knight>(BLACK));
    board[0][6]->setPiece(std::make_shared<Knight>(BLACK));
    board[7][1]->setPiece(std::make_shared<Knight>(WHITE));
    board[7][6]->setPiece(std::make_shared<Knight>(WHITE));

    // Bishops
    board[0][2]->setPiece(std::make_shared<Bishop>(BLACK));
    board[0][5]->setPiece(std::make_shared<Bishop>(BLACK));
    board[7][2]->setPiece(std::make_shared<Bishop>(WHITE));
    board[7][5]->setPiece(std::make_shared<Bishop>(WHITE));

    // Queens
    board[0][3]->setPiece(std::make_shared<Queen>(BLACK));
    board[7][3]->setPiece(std::make_shared<Queen>(WHITE));

    // Kings
    board[0][4]->setPiece(std::make_shared<King>(BLACK));
    board[7][4]->setPiece(std::make_shared<King>(WHITE));
}

void Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    auto piece = getTile(startRow, startCol)->getPiece();
    if (piece && piece->isValidMove(*this, startRow, startCol, endRow, endCol)) {
        std::shared_ptr<Piece> targetPiece = getTile(endRow, endCol)->getPiece();
        if (targetPiece) { // already do the check to make sure its not same colour in isvalidmove
            targetPiece.reset(); // Capture the opponent's piece
            // HANDLE REPORTING LOGIC TO GAME AFTER PIECE CAPTURE
        }

        // Castling logic (move rook if king moved two spaces)
        if (auto king = std::dynamic_pointer_cast<King>(piece)) {
            if (abs(startCol - endCol) == 2) {
                if (endCol == startCol + 2) {
                    // Kingside castling
                    auto rook = getTile(startRow, 7)->getPiece();
                    getTile(startRow, 5)->setPiece(rook);
                    getTile(startRow, 7)->setPiece(nullptr);
                } else if (endCol == startCol - 2) {
                    // Queenside castling
                    auto rook = getTile(startRow, 0)->getPiece();
                    getTile(startRow, 3)->setPiece(rook);
                    getTile(startRow, 0)->setPiece(nullptr);
                }
            }
        }

        // move the piece and set start tile to empty piece
        getTile(endRow, endCol)->setPiece(piece);
        getTile(startRow, startCol)->setPiece(nullptr);
        piece->setHasMoved(true);

        // Handle en passant flag for pawns
        if (auto pawn = std::dynamic_pointer_cast<Pawn>(piece)) {
            pawn->setEnPassantEligible(false);
            if (abs(startRow - endRow) == 2) { // will only be true after a pawn moves twice, otherwise always false
                pawn->setEnPassantEligible(true);
            }
        }
    }
}

void Board::setGameStatus(GameStatus status) {
    gameStatus = status;
}

void Board::render() {
    notifyObservers();
}

std::shared_ptr<Tile> Board::getTile(int row, int col) const {
    return board[row][col];
}

GameStatus Board::getStatus() const {
    return gameStatus;
}

int Board::getBoardSize() {
    return boardSize;
}

Board::~Board() {
    // do we need to delete anything if using smart pointer?
}
