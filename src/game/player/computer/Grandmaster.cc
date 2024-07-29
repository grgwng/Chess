#include "Grandmaster.h"
#include <limits>
#include <iostream>

Grandmaster::Grandmaster(Colour colour) : Computer(colour) {}

Move Grandmaster::computeMove(const shared_ptr<Board>& board) {
    int bestValue = INT_MIN;
    Move bestMove = invalidMove();
    std::vector<Move> validMoves = board->getAllValidMoves(colour);

    for (auto move : validMoves) {
        shared_ptr<Board> tempBoard = make_shared<Board>(*board);
        tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
        int boardValue = minimax(tempBoard, MAX_DEPTH - 1, false);

        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

    std::cout << "Best Move: " << bestMove.startRow << " " << bestMove.startCol << " " << bestMove.endRow << " " << bestMove.endCol << std::endl;
    return bestMove;
}

int Grandmaster::minimax(const shared_ptr<Board>& board, int depth, bool maximizingPlayer) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    Colour currentColour = maximizingPlayer ? colour : (colour == WHITE ? BLACK : WHITE);
    std::vector<Move> validMoves = board->getAllValidMoves(currentColour);

    if (validMoves.empty()) {
        return evaluateBoard(board);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(tempBoard, depth - 1, false);
            maxEval = max(maxEval, eval);
        }
        return maxEval;
    } 
    else {
        int minEval = INT_MAX; 
        for (auto move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(tempBoard, depth - 1, true);
            minEval = min(minEval, eval);
        }
        return minEval;
    }
}

int Grandmaster::evaluateBoard(const shared_ptr<Board>& board) {
    int score = 0;

    for (int row = 0; row < board->getBoardSize(); ++row) {
        for (int col = 0; col < board->getBoardSize(); ++col) {
            auto piece = board->getTile(row, col)->getPiece();
            if (piece) {
                int pieceValue = 0;
                switch (piece->getType()) {
                    case 'p': pieceValue = 1; break;
                    case 'n': pieceValue = 3; break;
                    case 'b': pieceValue = 3; break;
                    case 'r': pieceValue = 5; break;
                    case 'q': pieceValue = 9; break;
                    case 'k': pieceValue = 100; break;
                    default: break;
                }
                score += (piece->getColour() == colour) ? pieceValue : -pieceValue;
            }
        }
    }

    return score;
}
