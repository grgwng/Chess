
#include "Computer.h"
#include "../../entities/pieces/King.h"
#include <iostream>

Computer::Computer(Colour colour): Player{colour} {}

Move Computer::makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board){
    shared_ptr<Command> command = interpreter->readCommand();

    if(!command){
        return invalidMove();
    }

    switch(command->getType()){
        case MOVE: {
            shared_ptr<MoveCommand> mc = dynamic_pointer_cast<MoveCommand>(command);
            if(mc->getIsComputer()){
                return computeMove(board);
            }else{
                return invalidMove();
            }
            break;

        }
        case RESIGN:
            return resignMove(colour);
            break;
        case QUIT:
            return quitMove();
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

    for(const auto& move : validMoves) {
        shared_ptr<Board> tempboard = make_shared<Board>(*board);

        tempboard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);

        if(move.promotionType != '0') {
            tempboard->addPiece(move.endRow, move.endCol, move.promotionType, move.player);
        }

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

    for(const auto& move : validMoves) {
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
        for (int row = 0; row < board->getBoardSize(); row++) {
            for (int col = 0; col < board->getBoardSize(); col++) {
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

std::vector<Move> Computer::getAvoidingMoves(const shared_ptr<Board>& board, Colour colour) {
    std::vector<Move> validMoves = getComputerValidMoves(board, colour);
    std::vector<Move> avoidMoves;
    std::vector<std::pair<int, int>> threatenedPieces;

    for (int row = 0; row < board->getBoardSize(); row++) {
        for (int col = 0; col < board->getBoardSize(); col++) {
            auto piece = board->getTile(row, col)->getPiece();
            if (piece && piece->getColour() == colour) {
                bool underAttack = false;
                for (int oppRow = 0; oppRow < board->getBoardSize(); oppRow++) {
                    for (int oppCol = 0; oppCol < board->getBoardSize(); oppCol++) {
                        auto opponentPiece = board->getTile(oppRow, oppCol)->getPiece();
                        if (opponentPiece && opponentPiece->getColour() != colour) {
                            auto opponentMoves = opponentPiece->getValidMoves(*board, oppRow, oppCol);
                            for (const auto& opponentMove : opponentMoves) {
                                if (opponentMove.endRow == row && opponentMove.endCol == col) {
                                    underAttack = true;
                                    break;
                                }
                            }
                        }
                        if (underAttack) break;
                    }
                    if (underAttack) break;
                }
                if (underAttack) {
                    threatenedPieces.push_back(std::make_pair(row, col));
                }
            }
        }
    }

    for (const auto& piecePos : threatenedPieces) {
        auto piece = board->getTile(piecePos.first, piecePos.second)->getPiece();
        if (piece) {
            auto pieceMoves = piece->getValidMoves(*board, piecePos.first, piecePos.second);
            for (const auto& move : pieceMoves) {
                shared_ptr<Board> tempBoard = make_shared<Board>(*board);
                tempBoard->movePiece(move.startRow, move.startCol, move.endRow, move.endCol);

                bool isSafe = true;
                for (int row = 0; row < board->getBoardSize(); ++row) {
                    for (int col = 0; col < board->getBoardSize(); ++col) {
                        auto opponentPiece = tempBoard->getTile(row, col)->getPiece();
                        if (opponentPiece && opponentPiece->getColour() != colour) {
                            auto opponentMoves = opponentPiece->getValidMoves(*tempBoard, row, col);
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
                    avoidMoves.push_back(move);
                }
            }
        }
    }

    return avoidMoves;
}
