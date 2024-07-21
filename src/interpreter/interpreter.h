#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "commands.h"
#include <unordered_map>
#include <unordered_set>


class Interpreter{
    unordered_map<string, PlayerType> playerTypeParseTable;
    unordered_map<string, Colour> colourParseTable; 
    unordered_set<char> pieceTable;

    vector<int> parsePos(string);

    public:
        Interpreter();
        ~Interpreter();
        Command* readCommand();


};

#endif