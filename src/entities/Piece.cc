#include "Piece.h"
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
                Move newMove{colour, startRow, startCol, row, col,'0', false};
                result.push_back(newMove);
            }
        }
    }

    return result;
}