#ifndef NOOB_H
#define NOOB_H

#include "../Computer.h"

class Noob : public Computer {
public:
    void makeMove() override;
};

#endif