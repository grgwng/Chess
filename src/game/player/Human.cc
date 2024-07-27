#include "Human.h"
#include <iostream>

Human::Human(){}

Move Human::makeMove(Interpreter& interpreter){

    Command* c= interpreter.readCommand();
    cout << "hello" << endl;

    

}