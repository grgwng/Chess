#include "Noob.h"
#include <random>

Noob::Noob(Colour colour): Computer{colour} {}

Move Noob::computeMove(const shared_ptr<Board>& board){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::uniform_int_distribution<> distr(0, validMoves.size() - 1);
    return validMoves.at(distr(gen));
}