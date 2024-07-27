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
    std::shared_ptr<Tile> whiteKingTile;
    std::shared_ptr<Tile> blackKingTile;
    GameStatus gameStatus;
public:
    Board();
    std::shared_ptr<Tile> getWhiteKingTile() const;
    std::shared_ptr<Tile> getBlackKingTile() const;
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    void promotePawn(int row, int col, char newPieceType);
    void setGameStatus(GameStatus status);
    void render();
    std::shared_ptr<Tile> getTile(int row, int col) const;
    GameStatus getStatus() const;
    int getBoardSize();
    ~Board();
};

#endif