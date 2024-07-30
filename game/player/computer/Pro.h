#ifndef PRO_H
#define PRO_H

#include "../Computer.h"

class Pro : public Computer {
protected:
    Move computeMove(const shared_ptr<Board>& board) override;
public:
    Pro(Colour colour);
};

#endif
