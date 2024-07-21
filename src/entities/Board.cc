#include "Board.h"
#include "Colour.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Board::Board() {
    for(int row = 0; row < boardSize; row++) {
        for(int col = 0; col < boardSize; col++) {
            Colour curColour = Colour::WHITE;

            if(row % 2 == 0) {
                if(col % 2 == 0) {
                    curColour = Colour::WHITE;
                }
                else {
                    curColour = Colour::BLACK;
                }
            }
            else {
                if(col % 2 == 0) {
                    curColour = Colour::BLACK;
                }
                else {
                    curColour = Colour::WHITE;
                }
            }

            Tile* newTile = new Tile{curColour};

            board[row][col] = newTile;
        }
    }

    // Set up default pieces
    
    // Pawns
    for(int col = 0; col < boardSize; col++) {
        board[1][col]->setPiece(new Pawn(Colour::BLACK));
        board[6][col]->setPiece(new Pawn(Colour::WHITE));
    }

    // Rooks
    board[0][0]->setPiece(new Rook(Colour::BLACK));
    board[0][7]->setPiece(new Rook(Colour::BLACK));
    board[7][0]->setPiece(new Rook(Colour::WHITE));
    board[7][7]->setPiece(new Rook(Colour::WHITE));

    // Knights
    board[0][1]->setPiece(new Knight(Colour::BLACK));
    board[0][6]->setPiece(new Knight(Colour::BLACK));
    board[7][1]->setPiece(new Knight(Colour::WHITE));
    board[7][6]->setPiece(new Knight(Colour::WHITE));

    // Bishops
    board[0][2]->setPiece(new Bishop(Colour::BLACK));
    board[0][5]->setPiece(new Bishop(Colour::BLACK));
    board[7][2]->setPiece(new Bishop(Colour::WHITE));
    board[7][5]->setPiece(new Bishop(Colour::WHITE));

    // Queens
    board[0][3]->setPiece(new Queen(Colour::BLACK));
    board[7][3]->setPiece(new Queen(Colour::WHITE));

    // Kings
    board[0][4]->setPiece(new King(Colour::BLACK));
    board[7][4]->setPiece(new King(Colour::WHITE));
}

void Board::movePiece() {
    // TO DO!!!!
}

void Board::render() {
    notifyObservers();
}

Tile* Board::getTile(int row, int col) const {
    return board[row][col];
}

int Board::getBoardSize() {
    return boardSize;
}

Board::~Board() {
    // TO DO!!!!
}


