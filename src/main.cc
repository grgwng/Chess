#include "entities/Board.h"
#include "display/TextDisplay.h"
#include "game/Game.h"

#include <iostream>
#include <map>

int main() {
    Game game;

    game.runProgram();


    Board newBoard{};
    std::shared_ptr<TextDisplay> textDisplay = make_shared<TextDisplay>(&newBoard);
    newBoard.initializeStandardBoard();
    newBoard.render();

    std::vector<Move> validMoves = newBoard.getAllValidMoves(BLACK);

    std::map<char, int> rowMapping = {
        {'8', 0},
        {'7', 1},
        {'6', 2},
        {'5', 3},
        {'4', 4},
        {'3', 5},
        {'2', 6},
        {'1', 7}
    };

    std::map<char, int> colMapping = {
        {'A', 0},
        {'B', 1},
        {'C', 2},
        {'D', 3},
        {'E', 4},
        {'F', 5},
        {'G', 6},
        {'H', 7}
    };

    while (true) {
        char startColLetter, startRowNumber, endColLetter, endRowNumber;
        std::cin >> startColLetter >> startRowNumber >> endColLetter >> endRowNumber;
        int startRow = rowMapping[startRowNumber];
        int startCol = colMapping[startColLetter];
        int endRow = rowMapping[endRowNumber];
        int endCol = colMapping[endColLetter];
        bool validMove = newBoard.movePiece(startRow, startCol, endRow, endCol);
        newBoard.render();
        if (!validMove) {
            std::cout << "Invalid move" << std::endl;
        } else {
            std::cout << "Valid move" << std::endl;
        }
    }
}