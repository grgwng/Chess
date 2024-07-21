#include "Board.h"
#include "../types/types.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Board::Board() {
    board.resize(boardSize, vector<Tile*>(boardSize, nullptr));
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

            Tile* newTile = new Tile{row, col, curColour};

            board[row][col] = newTile;
        }
    }

    // Set up default pieces
    
    // Pawns
    for(int col = 0; col < boardSize; col++) {
        board[1][col]->setPiece(new Pawn(BLACK));
        board[6][col]->setPiece(new Pawn(WHITE));
    }

    // Rooks
    board[0][0]->setPiece(new Rook(BLACK));
    board[0][7]->setPiece(new Rook(BLACK));
    board[7][0]->setPiece(new Rook(WHITE));
    board[7][7]->setPiece(new Rook(WHITE));

    // Knights
    board[0][1]->setPiece(new Knight(BLACK));
    board[0][6]->setPiece(new Knight(BLACK));
    board[7][1]->setPiece(new Knight(WHITE));
    board[7][6]->setPiece(new Knight(WHITE));

    // Bishops
    board[0][2]->setPiece(new Bishop(BLACK));
    board[0][5]->setPiece(new Bishop(BLACK));
    board[7][2]->setPiece(new Bishop(WHITE));
    board[7][5]->setPiece(new Bishop(WHITE));

    // Queens
    board[0][3]->setPiece(new Queen(BLACK));
    board[7][3]->setPiece(new Queen(WHITE));

    // Kings
    board[0][4]->setPiece(new King(BLACK));
    board[7][4]->setPiece(new King(WHITE));
}

void Board::movePiece() {
    // TO DO!!!!
}

void Board::setGameStatus(GameStatus status) {
    gameStatus = status;
}

void Board::render() {
    notifyObservers();
}

Tile* Board::getTile(int row, int col) const {
    return board[row][col];
}

GameStatus Board::getStatus() const {
    return gameStatus;
}

int Board::getBoardSize() {
    return boardSize;
}

Board::~Board() {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            delete board[row][col];
        }
    }
}
