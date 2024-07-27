#ifndef GAME_H
#define GAME_H

#include "../entities/Board.h"
#include <vector>
#include "../interpreter/interpreter.h"
#include "player/Player.h"
#include "Move.h"
#include "Board.h"
#include "../entities/pieces/King.h"

using namespace std;

enum class GameState{DEFAULT, GAME, SETUP};

class Game {
    std::shared_ptr<Board> board;
    std::unique_ptr<Interpreter> interpreter;

    Player* player1;
    Player* player2;

    GameState state = GameState::DEFAULT;

    vector<Move> moveHistory;
public:
    Game();

    void runProgram();
    void gameLoop();
    void setupLoop();

    void makeMove();

    bool checkCheck(Colour colour); //checks if colour is in check
    bool checkCheckmate(Colour colour); 
    bool checkStalemate(Colour colour);
    bool checkPromotion(Colour colour);

    bool checkDraw();

    void resign();

    ~Game();
};

#endif