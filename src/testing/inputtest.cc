#include "../interpreter/interpreter.h"
#include "../interpreter/commands.h"
#include "../types/types.h"
#include <string>
#include <iostream>
using namespace std;


int main(){
    Interpreter i = Interpreter{};
    

    while(true){

        Command* c = i.readCommand();
        if(c){
            cout << c->getType() << endl;
            if(c->getType() == MOVE){
                Move* s = static_cast<Move*>(c);
                cout << s->getStartPos()[0]  << s->getStartPos()[1] << endl;
                // cout << s->getPiece() << endl;
                cout << s->getEndPos()[0]  << s->getEndPos()[1] << endl;
                cout << s->getIsComputer() << endl;
                cout << s->getConvertToPiece() << endl;
            }
        }else{
            cout << "Invalid command" << endl;
        }

    }




}