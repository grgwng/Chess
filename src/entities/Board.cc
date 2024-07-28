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

Board::Board(const Board& other) : gameStatus{other.gameStatus} {
    board.resize(boardSize, vector<std::shared_ptr<Tile>>(boardSize));

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            board[row][col] = std::make_shared<Tile>(*other.board[row][col]);
        }
    }

    if (other.whiteKingTile) {
        whiteKingTile = board[other.whiteKingTile->getRow()][other.whiteKingTile->getCol()];
    }
    if (other.blackKingTile) {
        blackKingTile = board[other.blackKingTile->getRow()][other.blackKingTile->getCol()];
    }
}

void Board::clearBoard(){
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            removePiece(row, col);
        }
    }

    whiteKingTile = nullptr;
    blackKingTile = nullptr;
}

void Board::initializeStandardBoard() {
    // Pawns
    for(int col = 0; col < boardSize; col++) {
        setTile(1, col, std::make_shared<Pawn>(BLACK));
        setTile(6, col, std::make_shared<Pawn>(WHITE));
    }

    // Rooks
    setTile(0, 0, std::make_shared<Rook>(BLACK));
    setTile(0, 7, std::make_shared<Rook>(BLACK));
    setTile(7, 0, std::make_shared<Rook>(WHITE));
    setTile(7, 7, std::make_shared<Rook>(WHITE));

    // Knights
    setTile(0, 1, std::make_shared<Knight>(BLACK));
    setTile(0, 6, std::make_shared<Knight>(BLACK));
    setTile(7, 1, std::make_shared<Knight>(WHITE));
    setTile(7, 6, std::make_shared<Knight>(WHITE));

    // Bishops
    setTile(0, 2, std::make_shared<Bishop>(BLACK));
    setTile(0, 5, std::make_shared<Bishop>(BLACK));
    setTile(7, 2, std::make_shared<Bishop>(WHITE));
    setTile(7, 5, std::make_shared<Bishop>(WHITE));

    // Queens
    setTile(0, 3, std::make_shared<Queen>(BLACK));
    setTile(7, 3, std::make_shared<Queen>(WHITE));

    // Kings
    setTile(0, 4, std::make_shared<King>(BLACK));
    setTile(7, 4, std::make_shared<King>(WHITE));

    blackKingTile = board[0][4];
    whiteKingTile = board[7][4];
}

std::vector<Move> Board::getAllValidMoves(Colour colour) {
    std::vector<Move> validMoves;
    for(int row = 0; row < boardSize; row++) {
        for(int col = 0; col < boardSize; col++) {
            auto curPiece = getTile(row, col)->getPiece();
            if(curPiece && curPiece->getColour() == colour) {
                std::vector<Move> pieceMoves = curPiece->getValidMoves(*this, row, col);
                validMoves.insert(validMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return validMoves;
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
        setTile(row, col, nullptr);
    }
    setTile(row, col, newPiece);
}

bool Board::removePiece(int row, int col) {
    auto tile = board[row][col];
    auto piece = tile->getPiece();

    if(!piece) {
        return false;
    }

    setTile(row, col, nullptr);
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
        if(board[boardSize - 1][col]->getPiece() && board[boardSize - 1][col]->getPiece()->getType() == 'p') {
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
    auto piece = board[startRow][startCol]->getPiece();
    if (piece && piece->isValidMove(*this, startRow, startCol, endRow, endCol)) {
        std::shared_ptr<Piece> targetPiece = board[endRow][endCol]->getPiece();
        // if theres a piece on tile you're moving to then it must be an enemy piece and delete it
        if (targetPiece) { // already do the check to make sure its not same colour in isvalidmove
            setTile(endRow, endCol, nullptr); // Capture the opponent's piece
        }

        // move the piece and set start tile to empty piece
        setTile(endRow, endCol, piece);
        setTile(startRow, startCol, nullptr);
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
                std::shared_ptr<Piece> enPassantPawn = board[startRow][endCol]->getPiece();
                if (enPassantPawn && enPassantPawn->getType() == 'p' && enPassantPawn->getColour() != pawn->getColour() &&
                    dynamic_pointer_cast<Pawn>(enPassantPawn)->isEnPassantEligible()) {
                    setTile(startRow, endCol, nullptr); // capture the en passant pawn
                }
            }
        }

        // King logic 
        if (auto king = std::dynamic_pointer_cast<King>(piece)) {
            if (king->getColour() == Colour::WHITE) {
                whiteKingTile = board[endRow][endCol];
            } else {
                blackKingTile = board[endRow][endCol];
            }
            // castling: (move rook if king moved two spaces)
            if (abs(startCol - endCol) == 2) {
                if (endCol == startCol + 2) {
                    // Kingside castling
                    auto rook = board[startRow][7]->getPiece();
                    setTile(startRow, 5, rook);
                    setTile(startRow, 7, nullptr);
                } else if (endCol == startCol - 2) {
                    // Queenside castling
                    auto rook = board[startRow][0]->getPiece();
                    setTile(startRow, 3, rook);
                    setTile(startRow, 0, nullptr);
                }
            }
        }

        return true;
    }
    return false;
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

void Board::setTile(int row, int col, shared_ptr<Piece> p) {
    board[row][col]->setPiece(p);
}

GameStatus Board::getStatus() const {
    return gameStatus;
}

int Board::getBoardSize() const {
    return boardSize;
}
