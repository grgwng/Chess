#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "Observer.h"
#include "../entities/Board.h"
#include "Window.h"
#include <vector>

using namespace std;

class GraphicDisplay : public Observer {
    Board* iWatch;
    Xwindow xw;
    std::vector<std::vector<char>> buffer;

    void drawBoard();
    void drawTile(int, int);

public:
    GraphicDisplay(Board* s);
    ~GraphicDisplay();
    void notify() override;
};

#endif
