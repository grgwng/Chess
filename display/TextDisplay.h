#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <memory>

#include "Observer.h"
#include "../entities/Board.h"

using namespace std;

class TextDisplay : public Observer, public enable_shared_from_this<TextDisplay>  {
    std::shared_ptr<Board> iWatch;
    ostream &out = cout;
public:
    TextDisplay(std::shared_ptr<Board> b);
    ~TextDisplay();
    void notify() override;
};

#endif
