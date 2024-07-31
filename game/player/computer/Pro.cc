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
    std::vector<Move> avoidingMoves = getAvoidingMoves(board, colour);

    std::vector<Move> safeAndCheckMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          checkMoves.begin(), checkMoves.end(),
                          std::back_inserter(safeAndCheckMoves));

    std::vector<Move> avoidingAndCheckMoves;
    std::set_intersection(avoidingMoves.begin(), avoidingMoves.end(),
                          checkMoves.begin(), checkMoves.end(),
                          std::back_inserter(avoidingAndCheckMoves));

    std::vector<Move> safeAndCaptureMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(safeAndCaptureMoves));

    std::vector<Move> avoidingAndCaptureMoves;
    std::set_intersection(avoidingMoves.begin(), avoidingMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(avoidingAndCaptureMoves));

    std::vector<Move> checkAndCaptureMoves;
    std::set_intersection(checkMoves.begin(), checkMoves.end(),
                          captureMoves.begin(), captureMoves.end(),
                          std::back_inserter(checkAndCaptureMoves));
    
    std::vector<Move> avoidingAndSafeMoves;
    std::set_intersection(avoidingMoves.begin(), avoidingMoves.end(),
                          safeMoves.begin(), safeMoves.end(),
                          std::back_inserter(avoidingAndCaptureMoves));

    std::vector<Move> safeAndCheckAndCaptureMoves;
    std::set_intersection(safeMoves.begin(), safeMoves.end(),
                          checkAndCaptureMoves.begin(), checkAndCaptureMoves.end(),
                          std::back_inserter(safeAndCheckAndCaptureMoves));

    std::vector<Move> avoidingAndCheckAndCaptureMoves;
    std::set_intersection(avoidingMoves.begin(), avoidingMoves.end(),
                          checkAndCaptureMoves.begin(), checkAndCaptureMoves.end(),
                          std::back_inserter(avoidingAndCheckAndCaptureMoves));

    std::vector<Move> safeOrCheckOrCaptureMoves;
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), checkMoves.begin(), checkMoves.end());
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), captureMoves.begin(), captureMoves.end());
    safeOrCheckOrCaptureMoves.insert(safeOrCheckOrCaptureMoves.end(), safeMoves.begin(), safeMoves.end());

    if(!avoidingAndCheckAndCaptureMoves.empty()) {
        moves = avoidingAndCheckAndCaptureMoves;
    }
    else if(!avoidingAndCheckMoves.empty()) {
        moves = avoidingAndCheckMoves;
    }
    else if(!avoidingAndCaptureMoves.empty()) {
        moves = avoidingAndCaptureMoves;
    }
    else if(!avoidingAndSafeMoves.empty()) {
        moves = avoidingAndSafeMoves;
    }
    else if(!avoidingMoves.empty()) {
        moves = avoidingMoves;
    }
    else if(!safeAndCheckAndCaptureMoves.empty()) {
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
