#include "TextDisplay.h"
#include "../types/types.h"
#include <iostream>

TextDisplay::TextDisplay(Board* s): iWatch{s} {
    iWatch->attach(this);
}

TextDisplay::~TextDisplay() {
    iWatch->detach(this);
}

void TextDisplay::notify() {
    int size = iWatch->getBoardSize();

    for(int row = 0; row < size; row++) {
        out << size - row << " ";
        for(int col = 0; col < size; col++) {
            std::shared_ptr<Tile> curTile = iWatch->getTile(row, col);
            std::shared_ptr<Piece> curPiece = curTile->getPiece();

            if(curPiece == nullptr) {
                char tileChar = curTile->getColour() == WHITE ? ' ' : '_'; 
                out << tileChar;
            }
            else {
                char pieceChar = curPiece->getType();
                Colour pieceColour = curPiece->getColour();

                if(pieceColour == BLACK) {
                    out << pieceChar;
                }
                else if(pieceColour == WHITE) {
                    char upperPieceChar = toupper(pieceChar);
                    out << upperPieceChar;
                }
            }
        }
        out << endl;
    }

    out << endl;
    out << "  ";
    
    for(int i = 0; i < size; i++) {
        char c = 'a' + i;
        out << c;
    }

    out << endl;
}