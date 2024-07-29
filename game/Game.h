#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "../entities/Board.h"
#include "../interpreter/Interpreter.h"
#include "player/Player.h"
#include "Move.h"
#include "../entities/Board.h"
#include "../entities/pieces/King.h"
#include "../entities/pieces/Pawn.h"
#include "../display/TextDisplay.h"
#include "../display/GraphicDisplay.h"

using namespace std;

enum class GameState{DEFAULT, GAME, SETUP};

class Game {
    std::shared_ptr<Board> board;
    std::unique_ptr<Interpreter> interpreter;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    double p1score = 0;
    double p2score = 0;

    int nextPlayer = 1;

    std::shared_ptr<TextDisplay> textDisplay;
    std::shared_ptr<GraphicDisplay> graphicDisplay;
public:
    Game();

    void runProgram();
    void gameLoop();
    void setupLoop();
    bool canMakeLegalMove(Colour colour);
    bool checkCheck(Colour colour, const shared_ptr<Board>&); //checks if colour is in check
    bool checkCheckmate(Colour colour); 
    bool checkStalemate(Colour colour);
    bool checkPromotion(const shared_ptr<Board>& board, Move move);

    ~Game();
};

#endif
