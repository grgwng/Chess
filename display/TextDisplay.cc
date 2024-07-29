#include "TextDisplay.h"
#include "../types/types.h"
#include <iostream>

TextDisplay::TextDisplay(std::shared_ptr<Board> s): iWatch{s} {
    // iWatch->attach(shared_from_this());
}

TextDisplay::~TextDisplay() {
    iWatch->detach(shared_from_this());
}

void TextDisplay::notify() {
    out << endl;
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

    GameStatus status = iWatch->getStatus();

    if(status != NOSTATUS) {
        out << endl;

        switch(status) {
            case WHITECHECK:
                out << "White is in check.";
                break;
            case BLACKCHECK:
                out << "Black is in check.";
                break;
            case CHECKMATEWHITE: 
                out << "Checkmate! White wins!";
                break;
            case CHECKMATEBLACK:
                out << "Checkmate! Black wins!";
                break;
            case WHITEWINS:
                out << "White wins!";
                break;
            case BLACKWINS:
                out << "Black wins!";
                break;
            case STALEMATE:
                out << "Stalemate!";
                break;
            default:
                break;
        }

        out << endl;
    }

    out << endl;
}
