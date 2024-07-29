#include "Grandmaster.h"

Grandmaster::Grandmaster(Colour colour) : Computer(colour) {}

Move Grandmaster::computeMove(const shared_ptr<Board>& board) {
    int bestValue = std::numeric_limits<int>::min();
    Move bestMove = invalidMove();
    std::vector<Move> validMoves = board->getAllValidMoves(colour);

    for (const auto& move : validMoves) {
        shared_ptr<Board> tempBoard = make_shared<Board>(*board);
        tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);

        if(move.promotionType != '0') {
            tempBoard->addPiece(move.endRow, move.endCol, move.promotionType, move.player);
        }

        int boardValue = minimax(tempBoard, MAX_DEPTH - 1, false, INT_MIN, INT_MAX);

        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

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
        int maxEval = INT_MIN;
        for (auto move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);

            if(move.promotionType != '0') {
                tempBoard->addPiece(move.endRow, move.endCol, move.promotionType, move.player);
            }

            int eval = minimax(tempBoard, depth - 1, false, alpha, beta);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (auto move : validMoves) {
            shared_ptr<Board> tempBoard = make_shared<Board>(*board);
            tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);

            if(move.promotionType != '0') {
                tempBoard->addPiece(move.endRow, move.endCol, move.promotionType, move.player);
            }
            
            int eval = minimax(tempBoard, depth - 1, true, alpha, beta);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
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
