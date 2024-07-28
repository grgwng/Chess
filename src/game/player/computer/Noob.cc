#include "Noob.h"
#include <random>

Noob::Noob(Colour colour): Computer{colour} {}

Move Noob::computeMove(const shared_ptr<Board>& board){
    std::vector<Move> validMoves = board->getAllValidMoves(colour);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, validMoves.size() - 1);

    int randomNum = distr(gen);

    return validMoves.at(randomNum);
}