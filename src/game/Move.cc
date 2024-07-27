#include "Move.h"

Move invalidMove(){
    return Move{WHITE, -1, -1, -1, -1, ' ', false};
}

Move resignMove(Colour c){
    return Move{c, -1, -1, -1, -1, ' ', true};
}