#ifndef PRO_H
#define PRO_H

#include "../Computer.h"

class Pro : public Computer {
public:
    Move computeMove(const shared_ptr<Board>& board) override;
};

#endif