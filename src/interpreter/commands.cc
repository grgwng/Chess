
#include "commands.h"

Command::Command(CommandType t): type{t}{}
Command::~Command(){}

StartGame::StartGame(PlayerType p1, PlayerType p2): Command(STARTGAME), player1{p1}, player2{p2}{}

PlayerType StartGame::getPlayer1(){
    return player1;
}
PlayerType StartGame::getPlayer2(){
    return player2;
}

Resign::Resign(): Command(RESIGN) {}


Move::Move(int startRow, int startCol, int endRow, int endCol, bool isComputer): Command(MOVE),
    startRow{startRow}, startCol{startCol}, endRow{endRow}, endCol{endCol}, isComputer{isComputer} {}

vector<int> Move::getStartPos(){
    return {startRow, startCol};
}

vector<int> Move::getEndPos(){
    return {endRow, endCol};
}

bool Move::getIsComputer(){
    return isComputer;
}

Setup::Setup(): Command(SETUP){}


AddPiece::AddPiece(int row, int col, char piece): Command(ADDPIECE),
    row{row}, col{col}, piece{piece} {}

vector<int> AddPiece::getPos(){
    return {row, col};
}

char AddPiece::getPiece() {
    return piece;
}

RemovePiece::RemovePiece(int row, int col): Command(REMOVEPIECE), row{row}, col{col} {}

vector<int> RemovePiece::getPos(){
    return {row, col};
}

SetColour::SetColour(int colour): Command(SETCOLOUR), colour{colour} {}

int SetColour::getColour(){
    return colour;
}

DoneSetup::DoneSetup(): Command(DONESETUP){
    
}




