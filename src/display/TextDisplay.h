#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "Observer.h"
#include "../Board.h"

using namespace std;

class TextDisplay : public Observer {
    Board* iWatch;
    ostream &out = cout;
public:
    TextDisplay(Board* b);
    ~TextDisplay();
    void notify() override;
};


#endif