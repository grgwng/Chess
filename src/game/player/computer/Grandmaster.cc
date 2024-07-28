#include "Grandmaster.h"
#include <limits>
#include <iostream>

Grandmaster::Grandmaster(Colour colour) : Computer(colour) {}

Move Grandmaster::computeMove(const shared_ptr<Board>& board) {
    int bestValue = std::numeric_limits<int>::min();
    Move bestMove = invalidMove();
    std::vector<Move> validMoves = board->getAllValidMoves(colour);

    for (const auto& move : validMoves) {
        shared_ptr<Board> tempBoard = make_shared<Board>(*board);
        tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
        int boardValue = minimax(tempBoard, MAX_DEPTH - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

    std::cout << "Best Move: " << bestMove.startRow << " " << bestMove.startCol << " " << bestMove.endRow << " " << bestMove.endCol << std::endl;
    return bestMove;
}

int Grandmaster::minimax(const shared_ptr<Board>& board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    Colour currentColour = maximizingPlayer ? colour : (colour == WHITE ? BLACK : WHITE);
    std::vector<Move> validMoves = board->getAllValidMoves(currentColour);

    if (validMoves.empty()) {
        return evaluateBoard(board);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(tempBoard, depth - 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();  // Correcting the initialization
        for (const auto& move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);
            int eval = minimax(tempBoard, depth - 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
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
                    case 'p': pieceValue = 10; break;
                    case 'n': pieceValue = 30; break;
                    case 'b': pieceValue = 30; break;
                    case 'r': pieceValue = 50; break;
                    case 'q': pieceValue = 90; break;
                    case 'k': pieceValue = 900; break;
                    default: break;
                }
                score += (piece->getColour() == colour) ? pieceValue : -pieceValue;
            }
        }
    }

    return score;
}
