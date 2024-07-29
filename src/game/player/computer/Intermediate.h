#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "../Computer.h"

class Intermediate : public Computer {
public:
    Intermediate(Colour colour);
    Move computeMove(const shared_ptr<Board>& board) override;
};

#endif
