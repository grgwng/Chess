#ifndef GRANDMASTER_H
#define GRANDMASTER_H

#include "../Computer.h"

class Grandmaster : public Computer {
public:
    Move computeMove(const shared_ptr<Board>& board) override;
};

#endif