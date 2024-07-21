#include "Board.h"
#include "../display/TextDisplay.h"

int main() {
    Board newBoard{};
    TextDisplay* textDisplay = new TextDisplay(&newBoard);
    newBoard.render();
}