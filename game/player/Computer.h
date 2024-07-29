#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include <random>

class Computer : public Player {
protected:
    std::vector<Move> getComputerValidMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getCheckMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getCaptureMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getSafeMoves(const shared_ptr<Board>& board, Colour colour);
public:
    Computer(Colour colour);
    virtual Move computeMove(const shared_ptr<Board>& board) = 0;
    Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board);
};

#endif
