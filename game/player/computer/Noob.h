#ifndef NOOB_H
#define NOOB_H

#include "../Computer.h"

class Noob : public Computer {
protected:
    Move computeMove(const shared_ptr<Board>& board) override;
public:
    Noob(Colour colour);
};

#endif
