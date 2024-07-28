#include "Human.h"
#include <iostream>

Human::Human(Colour colour): Player{colour} {}

Move Human::convertMoveCommandToMove(MoveCommand* mc){
    
    vector<int> startPos = mc->getStartPos();
    vector<int> endPos = mc->getEndPos();
    char promotionPiece = mc->getConvertToPiece();

    return Move{colour, startPos[0], startPos[1], endPos[0], endPos[1], promotionPiece, false};
}

Move Human::makeMove(const unique_ptr<Interpreter>& interpreter, const shared_ptr<Board>& board){

    Command* command = interpreter->readCommand();

    if(!command){
        return invalidMove();
    }

    switch(command->getType()){
        case MOVE:{
            MoveCommand* mc = static_cast<MoveCommand*>(command);

            if(!mc->getIsComputer()){
                return convertMoveCommandToMove(mc);
            }
            else{
                return invalidMove();
            }
            break;

        }
        case RESIGN:
            return resignMove(colour);
            break;
        default:
            return invalidMove();
    }
}
