#ifndef NOOB_H
#define NOOB_H

#include "../Computer.h"

class Noob : public Computer {
public:
    Move computeMove(const shared_ptr<Board>& board) override;
};

#endif