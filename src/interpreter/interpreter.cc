#include "interpreter.h"
#include <iostream>
using namespace std;


Interpreter::Interpreter() {}

Interpreter::~Interpreter(){}

Command* Interpreter::readCommand(){
    string command;

    while(cin >> command){
        if(command == "game"){
            

        }else if(command == "resign"){

        }else if(command == "move"){

        }else if(command == "setup"){
 
        }else if(command == "+"){ //add piece

        }else if(command == "-"){ //remove piece

        }else if(command == "="){ //set colour

        }else if(command == "done"){

        }else if (command == "quit"){
            break;
        }
    }

}