
#include "Computer.h"
#include <iostream>

Computer::Computer(Colour colour): Player{colour} {}

Move Computer::makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board){

    Command* command = interpreter->readCommand();

    if(!command){
        return invalidMove();
    }

    switch(command->getType()){
        case MOVE:
            return computeMove(board);
            break;
        case RESIGN:
            return resignMove(colour);
            break;
        default:
            return invalidMove();
    }
}