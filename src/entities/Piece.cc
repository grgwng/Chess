#include "Piece.h"
#include "./pieces/King.h"
#include "./Board.h"
#include <memory>

Piece::Piece(Colour colour) : colour{colour}, hasMovedFlag{false} {}

Piece::Piece(const Piece& other) : colour{other.colour}, hasMovedFlag{other.hasMovedFlag} {}

Colour Piece::getColour() const { return colour;};

bool Piece::hasMoved() const { return hasMovedFlag; }

void Piece::setHasMoved(bool moved) { hasMovedFlag = moved; }

std::vector<Move> Piece::getValidMoves(const Board& board, int startRow, int startCol) {
    std::vector<Move> result;

    for(int row = 0; row < board.getBoardSize(); row++) {
        for(int col = 0; col < board.getBoardSize(); col++) {
            if(isValidMove(board, startRow, startCol, row, col)) {
                shared_ptr<Board> tempboard = std::make_shared<Board>(board);
                tempboard->movePiece(startRow, startCol, row, col);
                std::shared_ptr<Tile> tempKingTile = (colour == WHITE) ? tempboard->getWhiteKingTile() : tempboard->getBlackKingTile();
                auto tempKing = std::dynamic_pointer_cast<King>(tempKingTile->getPiece());

                if (tempKing && tempKing->isInCheck(*tempboard, tempKingTile->getRow(), tempKingTile->getCol())) {
                    continue;
                }

                if(getType() == 'p' && (row == 0 || row == 7)) {
                    for(auto promotionStatus : {'r', 'n', 'b', 'q'}) {
                        Move newMove{colour, startRow, startCol, row, col, promotionStatus, false};
                        result.push_back(newMove);
                    }
                    continue;
                }

                Move newMove{colour, startRow, startCol, row, col, '0', false};
                result.push_back(newMove);
            }
        }
    }

    return result;
}