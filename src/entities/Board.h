#ifndef BOARD_H
#define BOARD_H

#include "../display/Subject.h"
#include <vector>
#include <iostream>
class Tile;
class Piece;
using namespace std;

class Board : public Subject {
    const int boardSize = 8;
    vector<vector<std::shared_ptr<Tile>>> board;
    std::shared_ptr<Piece> lastMovedPiece;
public:
    Board();
    void movePiece(int startRow, int startCol, int endRow, int endCol);
    void render();
    std::shared_ptr<Tile> getTile(int row, int col) const;
    int getBoardSize();
    ~Board();
};

#endif