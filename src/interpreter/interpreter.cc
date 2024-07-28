#include "interpreter.h"
#include <iostream>
#include <sstream>
using namespace std;


Interpreter::Interpreter(): pieceTable{{'p', 'P', 'r', 'R', 'n', 'N', 'b', 'B', 'q', 'Q', 'k', 'K'}}{
    //set up playerTypeParseTable

    playerTypeParseTable["human"] = HUMAN;
    playerTypeParseTable["computer1"] = COMPUTER1;
    playerTypeParseTable["computer2"] = COMPUTER2;
    playerTypeParseTable["computer3"] = COMPUTER3;
    playerTypeParseTable["computer4"] = COMPUTER4;

    //set up colourParseTable

    colourParseTable["white"] = WHITE;
    colourParseTable["black"] = BLACK;



}

Interpreter::~Interpreter(){}

vector<int> Interpreter::parsePos(string s){
    if(s.length() != 2){
        return {-1,  -1};
    }
    
    char colChar = s[0];
    char rowChar = s[1];

    if('a' <= colChar && colChar <= 'h' && '1' <= rowChar && rowChar <= '8'){
        //valid
        return {'8'-rowChar, colChar-'a'};
    }else{
        //invalid
        return {-1, -1};
    }
}

shared_ptr<Command*> Interpreter::readCommand(){
    string input;
    string command;

    getline(cin, input);

    istringstream iss(input);

    if(!(iss >> command)){
        return make_shared<Command*>(new Quit{});
    }

    if(command == "game"){
        string whitePlayer, blackPlayer;
        iss >> whitePlayer >> blackPlayer;

        if(playerTypeParseTable.find(whitePlayer) != playerTypeParseTable.end()
            && playerTypeParseTable.find(blackPlayer) != playerTypeParseTable.end()){
                
            return make_shared<Command*>(new StartGame{playerTypeParseTable[whitePlayer], playerTypeParseTable[blackPlayer]});
        }else{
            return make_shared<Command*>(nullptr);
        }

        
    }else if(command == "resign"){
        return make_shared<Command*>(new Resign{});

    }else if(command == "move"){
        string start, end;
        char promotion;
        if(iss >> start >> end){ 

            //get start and end positions
            vector<int> startPos = parsePos(start);
            vector<int> endPos = parsePos(end);
            
            //check if invalid
            if(startPos[0] == -1 || endPos[0] == -1){
                return make_shared<Command*>(nullptr);
            }
            
            if(iss >> promotion){ 
                //it is a promotion
                if(pieceTable.find(promotion) != pieceTable.end()){//check if promotion is valid
                    return make_shared<Command*>(new MoveCommand{startPos[0], startPos[1], endPos[0], endPos[1], false, promotion});
                }else{
                    return make_shared<Command*>(nullptr);
                }
                
            }else{
                //it is not a promotion
                return make_shared<Command*>(new MoveCommand{startPos[0], startPos[1], endPos[0], endPos[1], false, 0});
            }
        }else{

            if(start.length() == 0 && end.length() ==0){
                return make_shared<Command*>(new MoveCommand(0, 0, 0, 0, true, 0));
            }else{
                return make_shared<Command*>(nullptr);
            }

        }


    }else if(command == "setup"){
        return make_shared<Command*>(new Setup{});
 
    }else if(command == "+"){ //add piece
        char piece;
        string s;
        iss >> piece >> s;

        vector<int> pos = parsePos(s);

        if(pieceTable.find(piece) != pieceTable.end() && pos[0] != -1){
            //valid piece
            return make_shared<Command*>(new AddPiece{pos[0], pos[1], piece});
        }else{
            return make_shared<Command*>(nullptr);
        }


    }else if(command == "-"){ //remove piece
        string s;
        iss >> s;
        vector<int> pos = parsePos(s);

        if(pos[0] != -1){
            return make_shared<Command*>(new RemovePiece{pos[0], pos[1]});
        }else{
            return make_shared<Command*>(nullptr);
        }

    }else if(command == "="){ //set colour
        string colour;
        iss >> colour;

        if(colourParseTable.find(colour) != colourParseTable.end()){
            return make_shared<Command*>(new SetColour{colourParseTable[colour]});
        }else{
            return make_shared<Command*>(nullptr);
        }

    }else if(command == "done"){
        return make_shared<Command*>(new DoneSetup{});

    }else{
        return make_shared<Command*>(nullptr);
    }

}