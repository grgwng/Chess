#ifndef BOARD_H
#define BOARD_H

#include "../display/Subject.h"
#include <vector>
#include <iostream>
class Tile;
class Piece;
using namespace std;

class Board : public Subject {
    int boardSize = 8;
    vector<vector<Tile*>> board;
    Piece* lastMovedPiece;
public:
    Board();
    void movePiece();
    void render();
    Tile* getTile(int row, int col) const;
    int getBoardSize();
    ~Board();
};

#endif