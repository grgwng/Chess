#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "commands.h"
#include <unordered_map>
#include <unordered_set>
#include <string>


class Interpreter{
    unordered_map<string, PlayerType> playerTypeParseTable;
    unordered_map<string, Colour> colourParseTable; 
    unordered_set<char> pieceTable;

    vector<int> parsePos(string);

    public:
        Interpreter();
        ~Interpreter();
        std::shared_ptr<Command*> readCommand();


};

#endif