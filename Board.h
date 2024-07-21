#ifndef BOARD_H
#define BOARD_H

#include "Subject.h"
#include "Tile.h"
#include <vector>
using namespace std;

class Board : public Subject {
    vector<vector<Tile>> board;
    Piece lastMovedPiece;
public:
    void movePiece();
};

#endif