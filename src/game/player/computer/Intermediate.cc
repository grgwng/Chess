#include "Intermediate.h"
#include <random>

Intermediate::Intermediate(Colour colour): Computer{colour} {}

Move Intermediate::computeMove(const shared_ptr<Board>& board){ 
    std::vector<Move> moves;

    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::vector<Move> checkMoves = getCheckMoves(board, colour);
    std::vector<Move> captureMoves = getCaptureMoves(board, colour);
    
    std::vector<Move> checkAndCaptureMoves;
    std::set_intersection(checkMoves.begin(), checkMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(checkAndCaptureMoves));

    if(!checkAndCaptureMoves.empty()) {
        moves = checkAndCaptureMoves;
    }
    else if(!checkMoves.empty()) {
        moves = checkMoves;
    }
    else if(!captureMoves.empty()) {
        moves = captureMoves;
    }
    else {
        moves = validMoves;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, moves.size() - 1);
    return moves.at(distr(gen));
}
