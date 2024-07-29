#ifndef COMMANDS_H
#define COMMANDS_H

#include "../types/types.h"
#include <vector>
using namespace std;

class Command {
    CommandType type;

public:
    Command(CommandType);
    virtual ~Command() = 0;
    CommandType getType();
};

class StartGame : public Command {
    PlayerType whitePlayer;
    PlayerType blackPlayer;

public:
    StartGame(PlayerType, PlayerType);
    PlayerType getWhitePlayer();
    PlayerType getBlackPlayer();
};
 
class Resign: public Command {
public:
    Resign();
};

class MoveCommand: public Command {
    int startRow, startCol, endRow, endCol;
    char convertToPiece;
    bool isComputer;

public:
    MoveCommand(int startRow, int startCol, int endRow, int endCol, bool isComputer, char convertToPiece);
    vector<int> getStartPos();
    vector<int> getEndPos();
    char getConvertToPiece();
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
    Colour colour;
public:
    SetColour(Colour Colour);
    Colour getColour();
};

class DoneSetup: public Command {
public:
    DoneSetup();
};

class Quit: public Command {
public:
    Quit();
};

#endif
