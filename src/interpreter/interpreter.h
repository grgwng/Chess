#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "commands.h"


class Interpreter{
    
    public:
        Interpreter();
        ~Interpreter();
        Command* readCommand();
};

#endif