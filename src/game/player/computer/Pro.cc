#include "../../../entities/pieces/King.h"
#include "Pro.h"
#include <random>

Pro::Pro(Colour colour): Computer{colour} {}

Move Pro::computeMove(const shared_ptr<Board>& board){
    std::vector<Move> moves;

    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::vector<Move> safeMoves = getSafeMoves(board, colour);
    std::vector<Move> checkMoves = getCheckMoves(board, colour);
    std::vector<Move> captureMoves = getCaptureMoves(board, colour);

    std::vector<Move> safeAndCheckMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          checkMoves.begin(), checkMoves.end(),
                          std::back_inserter(safeAndCheckMoves));

    std::vector<Move> safeAndCaptureMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(safeAndCaptureMoves));

    std::vector<Move> checkAndCaptureMoves;
    std::set_intersection(checkMoves.begin(), checkMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(checkAndCaptureMoves));

    std::vector<Move> safeAndCheckAndCaptureMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          checkAndCaptureMoves.begin(), checkAndCaptureMoves.end(),
                          std::back_inserter(safeAndCheckAndCaptureMoves));

    std::vector<Move> safeOrCheckOrCaptureMoves;
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), checkMoves.begin(), checkMoves.end());
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), captureMoves.begin(), captureMoves.end());
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), safeMoves.begin(), safeMoves.end());

    if(!safeAndCheckAndCaptureMoves.empty()) {
        moves = safeAndCheckAndCaptureMoves;
    } 
    else if(!safeAndCheckMoves.empty()) {
        moves = safeAndCheckMoves;
    }
    else if(!safeAndCaptureMoves.empty()) {
        moves = safeAndCaptureMoves;
    }
    else if(!safeOrCheckOrCaptureMoves.empty()) {
        moves = safeOrCheckOrCaptureMoves;
    }
    else {
        moves = validMoves;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, moves.size() - 1);
    return moves.at(distr(gen));
}
