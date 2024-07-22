#include "Board.h"
#include "../display/TextDisplay.h"

int main() {
    Board newBoard{};
    std::shared_ptr<TextDisplay> textDisplay = make_shared<TextDisplay>(&newBoard);
    newBoard.setGameStatus(STALEMATE);
    newBoard.render();
}