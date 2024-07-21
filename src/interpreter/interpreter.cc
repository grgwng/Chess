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

Command* Interpreter::readCommand(){
    string input;
    string command;

    unordered_map<string, PlayerType> playerTypeParseTable;

    getline(cin, input);

    istringstream iss(input);

    iss >> command;

    if(command == "game"){
        string whitePlayer, blackPlayer;
        iss >> whitePlayer >> blackPlayer;

        if(playerTypeParseTable.find(whitePlayer) != playerTypeParseTable.end()
            && playerTypeParseTable.find(blackPlayer) != playerTypeParseTable.end()){

            return new StartGame{playerTypeParseTable[whitePlayer], playerTypeParseTable[blackPlayer]};
        }else{
            cout << "Invalid arguments. Please try again" << endl;
            return nullptr;
        }

        
    }else if(command == "resign"){
        return new Resign{};

    }else if(command == "move"){
        string start, end;
        char promotion;
        if(iss >> start >> end){ 

            //get start and end positions
            vector<int> startPos = parsePos(start);
            vector<int> endPos = parsePos(end);
            
            //check if invalid
            if(startPos[0] == -1 || endPos[0] == -1){
                cout << "Invalid argument. Please try again" << endl;
                return nullptr;
            }
            
            if(iss >> promotion){ 
                //it is a promotion
                if(pieceTable.find(promotion) != pieceTable.end()){//check if promotion is valid
                    return new Move{startPos[0], startPos[1], endPos[0], endPos[1], false, promotion};
                }else{
                    cout << "Invalid argument. Please try again" << endl;
                    return nullptr;
                }
                
            }else{
                //it is not a promotion
                return new Move{startPos[0], startPos[1], endPos[0], endPos[1], false, 0};
            }
        }else{
            return new Move(0, 0, 0, 0, true, 0);

        }


    }else if(command == "setup"){
        return new Setup{};
 
    }else if(command == "+"){ //add piece
        char piece;
        string s;
        iss >> piece >> s;

        vector<int> pos = parsePos(s);

        if(pieceTable.find(piece) != pieceTable.end() && pos[0] != -1){
            //valid piece
            return new AddPiece{pos[0], pos[1], piece};
        }else{
            cout << "Invalid arguments. Please try again" << endl;
            return nullptr;
        }


    }else if(command == "-"){ //remove piece
        string s;
        iss >> s;
        vector<int> pos = parsePos(s);

        if(pos[0] != -1){
            return new RemovePiece{pos[0], pos[1]};
        }else{
            cout << "Invalid argument. Please try again" << endl;
            return nullptr;
        }

    }else if(command == "="){ //set colour
        string colour;
        iss >> colour;

        if(colourParseTable.find(colour) != colourParseTable.end()){
            return new SetColour{colourParseTable[colour]};
        }else{
            cout << "Invalid argument. Please try again" << endl;
            return nullptr;
        }

    }else if(command == "done"){
        return new DoneSetup{};

    }else{
        cout << "Invalid command. Please try again" << endl;
        return nullptr;
    }

}