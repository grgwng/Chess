#include "../../../entities/pieces/King.h"
#include "Intermediate.h"
#include <random>

Intermediate::Intermediate(Colour colour): Computer{colour} {}

Move Intermediate::computeMove(const shared_ptr<Board>& board){
    std::vector<Move> validMoves = board->getAllValidMoves(colour);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Move> checkMoves;

    for(auto move : validMoves) {
        shared_ptr<Board> tempboard = make_shared<Board>(*board);
        tempboard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
        shared_ptr<Tile> otherKingTile = (colour == WHITE) ? tempboard->getBlackKingTile() : tempboard->getWhiteKingTile();
        auto otherKing = dynamic_pointer_cast<King>(otherKingTile->getPiece());

        if(otherKing->isInCheck(*tempboard, otherKingTile->getRow(), otherKingTile->getCol())) {
            checkMoves.push_back(move);
        }
    }

    if(!checkMoves.empty()) {
        std::uniform_int_distribution<> distr(0, checkMoves.size() - 1);
        int randomNum = distr(gen);
        return checkMoves.at(randomNum);
    }

    std::vector<Move> captureMoves;

    for(auto move : validMoves) {
        auto endTilePiece = board->getTile(move.endRow, move.endCol)->getPiece();
        if(endTilePiece && endTilePiece->getColour() != colour) {
            captureMoves.push_back(move);
        }
    }

    if(!captureMoves.empty()) {
        std::uniform_int_distribution<> distr(0, captureMoves.size() - 1);
        int randomNum = distr(gen);
        return captureMoves.at(randomNum);
    }

    std::uniform_int_distribution<> distr(0, validMoves.size() - 1);
    int randomNum = distr(gen);
    return validMoves.at(randomNum);
}
