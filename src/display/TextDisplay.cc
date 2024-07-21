#include "TextDisplay.h"
#include "Colour.h"
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
        for(int col = 0; col < size; col++) {
            out << size - row << " ";
            Tile* curTile = iWatch->getTile(row, col);
            Piece* curPiece = curTile->getPiece();

            if(curPiece == nullptr) {
                char tile = curTile->getColour() == Colour::WHITE ? ' ' : '_'; 
                cout << tile;
            }
            else {
                
            }
        }
        cout << endl;
    }

    out << endl;
    
    for(int i = 0; i < size; i++) {
        out << i + 'a';
    }

    out << endl;
}