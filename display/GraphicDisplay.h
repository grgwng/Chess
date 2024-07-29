#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include <vector>
#include <memory>

#include "Observer.h"
#include "../entities/Board.h"
#include "Window.h"

using namespace std;

class GraphicDisplay : public Observer, public enable_shared_from_this<GraphicDisplay> {
    std::shared_ptr<Board> iWatch;
    Xwindow xw;
    std::vector<std::vector<char>> buffer;

    void drawBoard();
    void drawTile(int, int);

public:
    GraphicDisplay(std::shared_ptr<Board> s);
    ~GraphicDisplay();
    void notify() override;
};

#endif
