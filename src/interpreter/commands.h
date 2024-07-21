#ifndef COMMANDS_H
#define COMMANDS_H

#include "types/types.h"
#include <vector>
using namespace std;

class Command {
    CommandType type;

    public:
        Command(CommandType);
        virtual ~Command() = 0;
        CommandType getType();
};

class StartGame : Command {
    PlayerType player1;
    PlayerType player2;

    public:
        StartGame(PlayerType, PlayerType);
        PlayerType getPlayer1();
        PlayerType getPlayer2();
};
 
class Resign: Command {
    public:
        Resign();
};

class Move: Command {
    int startRow, startCol, endRow, endCol;
    bool isComputer;

    public:
        Move(int startRow, int startCol, int endRow, int endCol, bool isComputer);
        vector<int> getStartPos();
        vector<int> getEndPos();
        bool getIsComputer();
};


class Setup: public Command {

    public:
        Setup();
};

class AddPiece: public Command {
    int row, col;
    char piece;
    public:
        AddPiece(int row, int col, char piece);
        vector<int> getPos();
        char getPiece();
};

class RemovePiece: public Command {
    int row, col;
    public:
        RemovePiece(int row, int col);
        vector<int> getPos();
};

class SetColour: public Command {
    int colour;
    public:
        SetColour(int colour);
        int getColour();
};

class DoneSetup: public Command {

    public:
        DoneSetup();
};

#endif