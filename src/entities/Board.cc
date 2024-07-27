#include "Board.h"
#include "../types/types.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"
#include <iostream>

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
}

void Board::initializeStandardBoard() {
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
    whiteKingTile = board[7][4];
    blackKingTile = board[0][4];
}

void Board::addPiece(int row, int col, char piece, Colour colour) {
    std::shared_ptr<Piece> newPiece;

    switch (piece) {
        case 'p':
            newPiece = std::make_shared<Pawn>(colour);
            break;
        case 'r':
            newPiece = std::make_shared<Rook>(colour);
            break;
        case 'n':
            newPiece = std::make_shared<Knight>(colour);
            break;
        case 'b':
            newPiece = std::make_shared<Bishop>(colour);
            break;
        case 'q':
            newPiece = std::make_shared<Queen>(colour);
            break;
        case 'k':
            newPiece = std::make_shared<King>(colour);

            if(colour == WHITE) {
                whiteKingTile = board[row][col];
            }
            else if(colour == BLACK) {
                blackKingTile = board[row][col];
            }

            break;
        default:
            break;
    }

    newPiece->setHasMoved(true);

    if(board[row][col]->getPiece()) {
        board[row][col]->setPiece(nullptr);
    }
    board[row][col]->setPiece(newPiece);
}

bool Board::removePiece(int row, int col) {
    auto tile = board[row][col];
    auto piece = tile->getPiece();

    if(!piece) {
        return false;
    }

    tile->setPiece(nullptr);
    return true;
}

bool Board::checkValidBoard() {
    bool seenWhiteKing = false;
    bool seenBlackKing = false;

    // Check for exactly one black and white king, and that they're not in check
    for(int row = 0; row < boardSize; row++) {
        for(int col = 0; col < boardSize; col++) {
            auto piece = board[row][col]->getPiece();
            if(piece && piece->getType() == 'k') {
                if(piece->getColour() == WHITE) {
                    if(seenWhiteKing) {
                        return false;
                    }
                    else {
                        seenWhiteKing = true;
                    }
                }
                else if(piece->getColour() == BLACK) {
                    if(seenBlackKing) {
                        return false;
                    }
                    else {
                        seenBlackKing = true;
                    }
                }

                auto king = std::dynamic_pointer_cast<King>(piece);
                if(king->isInCheck(*this, row, col)) {
                    return false;
                }
            }
        }
    }

    if(!seenWhiteKing || !seenBlackKing) {
        return false;
    }

    // Check no pawns on first or last row of the board
    for(int col = 0; col < boardSize; col++) {
        // First row
        if(board[0][col]->getPiece() && board[0][col]->getPiece()->getType() == 'p') {
            return false;
        }

        // Last row
        if(board[boardSize - 1][col]->getPiece() && board[0][col]->getPiece()->getType() == 'p') {
            return false;
        }
    } 

    return true;
}

std::shared_ptr<Tile> Board::getWhiteKingTile() const { 
    return whiteKingTile; 
}
    
std::shared_ptr<Tile> Board::getBlackKingTile() const { 
    return blackKingTile; 
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    auto piece = getTile(startRow, startCol)->getPiece();
    if (piece && piece->isValidMove(*this, startRow, startCol, endRow, endCol)) {
        std::shared_ptr<Piece> targetPiece = getTile(endRow, endCol)->getPiece();
        // if theres a piece on tile you're moving to then it must be an enemy piece and delete it
        if (targetPiece) { // already do the check to make sure its not same colour in isvalidmove
            getTile(endRow, endCol)->setPiece(nullptr); // Capture the opponent's piece
            // TODO: HANDLE REPORTING LOGIC TO GAME AFTER PIECE CAPTURE
        }

        // move the piece and set start tile to empty piece
        getTile(endRow, endCol)->setPiece(piece);
        getTile(startRow, startCol)->setPiece(nullptr);
        piece->setHasMoved(true);

        // Check for en passant capture
        if (auto pawn = dynamic_pointer_cast<Pawn>(piece)) {

            // turn en passant flag on if it's the first time moving the pawn
            pawn->setEnPassantEligible(false);
            if (abs(startRow - endRow) == 2) { // will only be true after a pawn moves twice, otherwise always false
                pawn->setEnPassantEligible(true);
            }

            // En Passant capture logic
            int direction = (pawn->getColour() == Colour::WHITE) ? -1 : 1;
            // If moving diagonally and target square is empty
            if (abs(startCol - endCol) == 1 && endRow == startRow + direction && !targetPiece) {
                // The en passant captured pawn is directly beside the end position
                std::shared_ptr<Piece> enPassantPawn = getTile(startRow, endCol)->getPiece();
                if (enPassantPawn && enPassantPawn->getType() == 'p' && enPassantPawn->getColour() != pawn->getColour() &&
                    dynamic_pointer_cast<Pawn>(enPassantPawn)->isEnPassantEligible()) {
                    getTile(startRow, endCol)->setPiece(nullptr);
                    std::cout << "EN PASSANT CAPTURE!\n";
                    // TODO: HANDLE EN PASSANT REPORTING LOGIC TO GAME AFTER PIECE CAPTURE
                }
            }

            // promotion logic
            if (endRow == 0 || endRow == 7) { // the pawn is ready to be promoted
                // TODO: HANDLE PROMOTION LOGIC need to call game to get the user input for which piece and then call promotePawn

            }
        }

        // King logic 
        if (auto king = std::dynamic_pointer_cast<King>(piece)) {
            if (king->getColour() == Colour::WHITE) {
                whiteKingTile = getTile(endRow, endCol);
            } else {
                blackKingTile = getTile(endRow, endCol);
            }
            // castling: (move rook if king moved two spaces)
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

        return true;
    }
    return false;
}

void Board::promotePawn(int row, int col, char newPieceType) {
    Colour c = getTile(row, col)->getColour();
    // pawn promotion 
    if (newPieceType == 'q') {
        getTile(row, col)->setPiece(std::make_shared<Queen>(c));
    }
    else if (newPieceType == 'r') {
        getTile(row, col)->setPiece(std::make_shared<Rook>(c));
    }
    else if (newPieceType == 'n') {
        getTile(row, col)->setPiece(std::make_shared<Knight>(c));
    }
    else if (newPieceType == 'b') {
        getTile(row, col)->setPiece(std::make_shared<Bishop>(c));
    }
    else {
        cout << "invalid input";
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
