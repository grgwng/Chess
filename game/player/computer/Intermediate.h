#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "../Computer.h"

class Intermediate : public Computer {
protected:
    Move computeMove(const shared_ptr<Board>& board) override;
public:
    Intermediate(Colour colour);
};

#endif
