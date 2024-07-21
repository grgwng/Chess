
#include "commands.h"

Command::Command(CommandType t): type{t}{}
Command::~Command(){}

CommandType Command::getType(){
    return type;
}

StartGame::StartGame(PlayerType wp, PlayerType bp): Command(STARTGAME), whitePlayer{wp}, blackPlayer{bp}{}

PlayerType StartGame::getWhitePlayer(){
    return whitePlayer;
}
PlayerType StartGame::getBlackPlayer(){
    return blackPlayer;
}

Resign::Resign(): Command(RESIGN) {}


Move::Move(int startRow, int startCol, int endRow, int endCol, bool isComputer, char convertToPiece): Command(MOVE),
    startRow{startRow}, startCol{startCol}, endRow{endRow}, endCol{endCol}, isComputer{isComputer}, convertToPiece{convertToPiece} {}

vector<int> Move::getStartPos(){
    return {startRow, startCol};
}

vector<int> Move::getEndPos(){
    return {endRow, endCol};
}

char Move::getConvertToPiece(){
    return convertToPiece;
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

SetColour::SetColour(Colour colour): Command(SETCOLOUR), colour{colour} {}

Colour SetColour::getColour(){
    return colour;
}

DoneSetup::DoneSetup(): Command(DONESETUP){

}




