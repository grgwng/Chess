#include "Board.h"
#include "../display/TextDisplay.h"
#include "../display/GraphicDisplay.h"

#include <iostream>
#include <map>

int main() {
    Board newBoard{};
    std::shared_ptr<TextDisplay> textDisplay = make_shared<TextDisplay>(&newBoard);
    std::shared_ptr<GraphicDisplay> graphicDisplay = make_shared<GraphicDisplay>(&newBoard);
    newBoard.setGameStatus(STALEMATE);
    newBoard.render();

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