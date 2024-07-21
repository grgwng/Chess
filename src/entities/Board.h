#ifndef BOARD_H
#define BOARD_H

#include "../display/Subject.h"
#include "Tile.h"
#include <vector>
using namespace std;

class Board : public Subject {
    int boardSize = 8;
    vector<vector<Tile*>> board;
    Piece lastMovedPiece;
public:
    Board();
    void movePiece();
    ~Board();
};

#endif