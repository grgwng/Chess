#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include <algorithm>
#include <random>

class Computer : public Player {
protected:
    std::vector<Move> getComputerValidMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getCheckMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getCaptureMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getSafeMoves(const shared_ptr<Board>& board, Colour colour);
    std::vector<Move> getAvoidingMoves(const shared_ptr<Board>& board, Colour colour);
    virtual Move computeMove(const shared_ptr<Board>& board) = 0;
public:
    Computer(Colour colour);
    Move makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board) override;
};

#endif
