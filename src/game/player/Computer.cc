
#include "Computer.h"
#include "../../entities/pieces/King.h"
#include <iostream>

Computer::Computer(Colour colour): Player{colour} {}

Move Computer::makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board){

    Command* command = interpreter->readCommand();

    if(!command){
        return invalidMove();
    }

    switch(command->getType()){
        case MOVE:
            return computeMove(board);
            break;
        case RESIGN:
            return resignMove(colour);
            break;
        default:
            return invalidMove();
    }
}

std::vector<Move> Computer::getComputerValidMoves(const shared_ptr<Board>& board, Colour colour) {
    return board->getAllValidMoves(colour);
}

std::vector<Move> Computer::getCheckMoves(const shared_ptr<Board>& board, Colour colour) {
    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
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

    return checkMoves;
}

std::vector<Move> Computer::getCaptureMoves(const shared_ptr<Board>& board, Colour colour) {
    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::vector<Move> captureMoves;

    for(auto move : validMoves) {
        auto endTilePiece = board->getTile(move.endRow, move.endCol)->getPiece();
        if(endTilePiece && endTilePiece->getColour() != colour) {
            captureMoves.push_back(move);
        }
    }

    return captureMoves;
}

std::vector<Move> Computer::getSafeMoves(const shared_ptr<Board>& board, Colour colour) {
    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::vector<Move> safeMoves;

    for (const auto& move : validMoves) {
        shared_ptr<Board> tempBoard = make_shared<Board>(*board);
        tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
        
        bool isSafe = true;
        for (int row = 0; row < board->getBoardSize(); ++row) {
            for (int col = 0; col < board->getBoardSize(); ++col) {
                auto piece = tempBoard->getTile(row, col)->getPiece();
                if (piece && piece->getColour() != colour) {
                    auto opponentMoves = piece->getValidMoves(*tempBoard, row, col);
                    for (const auto& opponentMove : opponentMoves) {
                        if (opponentMove.endRow == move.endRow && opponentMove.endCol == move.endCol) {
                            isSafe = false;
                            break;
                        }
                    }
                }
                if (!isSafe) break;
            }
            if (!isSafe) break;
        }

        if (isSafe) {
            safeMoves.push_back(move);
        }
    }

    return safeMoves;
}
