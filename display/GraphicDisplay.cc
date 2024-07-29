#include "GraphicDisplay.h"
#include "../types/types.h"

GraphicDisplay::GraphicDisplay(Board* b): 
    iWatch{b}, 
    xw{500, 600},
    buffer{std::vector<std::vector<char>>(b->getBoardSize(), std::vector<char>(b->getBoardSize(), ' '))} 
{
    iWatch->attach(this);
    drawBoard();
}

GraphicDisplay::~GraphicDisplay() {
    iWatch->detach(this);
}

void GraphicDisplay::notify() {
    for(int row = 0; row < iWatch->getBoardSize(); row++) {
        for(int col = 0; col < iWatch->getBoardSize(); col++) {
            std::shared_ptr<Piece> curPiece = iWatch->getTile(row, col)->getPiece();;
            char pieceChar = curPiece ? curPiece->getType() : ' ';

            if(curPiece && curPiece->getColour() == WHITE) {
                pieceChar = toupper(pieceChar);
            }
            
            if(buffer[row][col] != pieceChar) {
                buffer[row][col] = pieceChar;
                drawTile(row, col);

                if(curPiece) {
                    xw.drawString(69 + col * 50, 80 + row * 50, string{pieceChar}, curPiece->getColour() == WHITE ? Xwindow::White : Xwindow::Black, 20);
                }
            }
        }
    }

    GameStatus status = iWatch->getStatus();

    if(status != NOSTATUS) {
        string message;
        int xOffset = 0;

        switch(status) {
            case WHITECHECK:
                message = "White is in check.";
                xOffset = 100;
                break;
            case BLACKCHECK:
                message = "Black is in check.";
                xOffset = 100;
                break;
            case CHECKMATEWHITE: 
                message = "Checkmate! White wins!";
                xOffset = 135;
                break;
            case CHECKMATEBLACK:
                message = "Checkmate! Black wins!";
                xOffset = 135;
                break;
            case WHITEWINS:
                message = "White wins!";
                xOffset = 80;
                break;
            case BLACKWINS:
                message = "Black wins!";
                xOffset = 80;
                break;
            case STALEMATE:
                message = "Stalemate!";
                xOffset = 70;
                break;
            default:
                break;
        }

        xw.drawString(250 - xOffset, 500, message, Xwindow::Black, 25);
    }
    else {
        xw.fillRectangle(0, 460, 500, 200, Xwindow::Grey);
    }
}

void GraphicDisplay::drawBoard() {
    xw.fillRectangle(0, 0, 500, 600, Xwindow::Grey);

    xw.fillRectangle(40, 40, 420, 420, Xwindow::Black);
    
    for (int row = 0; row < iWatch->getBoardSize(); row++) {
        for (int col = 0; col < iWatch->getBoardSize(); col++) {
            drawTile(row, col);
        }
    }
}

void GraphicDisplay::drawTile(int row, int col) {
    bool colourCondition = (row + col) % 2 == 0;

    int colour = colourCondition ? Xwindow::TileLight : Xwindow::TileDark;
    xw.fillRectangle(50 + col * 50, 50 + row * 50, 50, 50, colour);

    if (col == 0) {
        xw.drawString(52, 65 + row * 50, std::to_string(iWatch->getBoardSize() - row), !colourCondition ? Xwindow::TileLight : Xwindow::TileDark, 12);
    }

    if (row == iWatch->getBoardSize() - 1) {
        xw.drawString(88 + col * 50, 445, std::string(1, 'a' + col), !colourCondition ? Xwindow::TileLight : Xwindow::TileDark, 12);
    }
}
