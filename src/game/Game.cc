#include "Game.h"
#include "../interpreter/commands.h"
#include "player/Human.h"
#include "player/computer/Noob.h"
#include "player/computer/Intermediate.h"
#include "player/computer/Pro.h"
#include "player/computer/Grandmaster.h"
#include <iostream>
using namespace std;

Game::Game(): board{std::make_shared<Board>()}, interpreter{std::make_unique<Interpreter>()}{}

Game::~Game(){

}

bool Game::checkCheck(Colour colour, const shared_ptr<Board>& board) {
    // Colour opponentColour = (colour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());
    return king->isInCheck(*board, kingTile->getRow(), kingTile->getCol());
}

bool Game::checkCheckmate(Colour colour) {
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());

    if (!king->isInCheck(*board, kingTile->getRow(), kingTile->getCol())) {
        return false;
    }

    // king must be in check now
    // Check if there is any legal move for the king to escape check. Iterate through all possible moves for the king
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            int newRow = kingTile->getRow() + rowOffset;
            int newCol = kingTile->getCol() + colOffset;
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (king->isValidMove(*board, kingTile->getRow(), kingTile->getCol(), newRow, newCol)) {
                    return true; // king has a valid move so can escape check
                }
            }
        }
    }

    // Check if there is any legal move for any piece of same colour to block the check or capture the attacking piece
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board->getTile(row, col)->getPiece();
            if (piece && piece->getColour() == colour) {
                for (int endRow = 0; endRow < 8; ++endRow) {
                    for (int endCol = 0; endCol < 8; ++endCol) {
                        if (piece->isValidMove(*board, row, col, endRow, endCol)) {
                            // Simulate the move
                            Board tempBoard = *board; // Make a copy of the board
                            tempBoard.movePiece(row, col, endRow, endCol);

                            // Check if the king is still in check after the move
                            if (!king->isInCheck(tempBoard, kingTile->getRow(), kingTile->getCol())) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true; // King is in checkmate
}


bool Game::checkStalemate(Colour colour) {
    std::shared_ptr<Tile> kingTile = (colour == Colour::WHITE) ? board->getWhiteKingTile() : board->getBlackKingTile();
    auto king = std::dynamic_pointer_cast<King>(kingTile->getPiece());
    if (king->isInCheck(*board, kingTile->getRow(), kingTile->getCol())) {
        return false;
    }

    // Check if there are any legal moves available for all pieces of a certain colour
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = board->getTile(row, col)->getPiece();
            if (piece && piece->getColour() == colour) {
                for (int endRow = 0; endRow < 8; ++endRow) {
                    for (int endCol = 0; endCol < 8; ++endCol) {
                        if (piece->isValidMove(*board, row, col, endRow, endCol)) {
                            return false; // Found a valid move so not stalemate
                        }
                    }
                }
            }
        }
    }

    return true; // No valid moves found
}

bool Game::checkPromotion(const shared_ptr<Board>& board, Move move) {
    return false;
}

bool Game::checkDraw() {

}

void Game::resign() {

}


void Game::gameLoop(){ 

    cout << "New game has started!" << endl;

    int activePlayer = 1;
    GameStatus status = NOSTATUS;

    board->initializeStandardBoard();

    //our loop in game mode

    while(true){

        //PLAYER1 input loop
        board->render();
        cout << "WHITE'S TURN" << endl;
        cout << "Enter a game command:" << endl;
        while(activePlayer == 1){
            //call makeMove for player1 (returns a Move class)
            Move player1Move = player1->makeMove(interpreter, board);

            if(player1Move.isResign){
                cout << "White resigned!" << endl;
                status = WHITERESIGN;
                break;
            }
    
            
            if(player1Move.startCol < 0){ //invalid move
                continue; //retry
            }

            //check if the move is a valid move
            if(!board->getTile(player1Move.startRow, player1Move.startCol)->getPiece() ||
                board->getTile(player1Move.startRow, player1Move.startCol)->getPiece()->getColour() != WHITE ||
                !board->getTile(player1Move.startRow, player1Move.startCol)->getPiece()
                ->isValidMove(*board, player1Move.startRow, player1Move.startCol, player1Move.endRow, player1Move.endCol)){
            
                //not valid move
                cout << "Invalid piece move. Please try again." << endl;
                continue;
            }


            //make tempboard
            //check if player1 in check, if yes reject
            shared_ptr<Board> tempboard = make_shared<Board>(*board);
            tempboard->movePiece(player1Move.startRow, player1Move.startCol, player1Move.endRow, player1Move.endCol);

            
            if(checkCheck(WHITE, tempboard)){
                cout << "White put itself in check. Invalid move." << endl;
                continue;
            }

            //check if we have everything for a promotion if relevant
            if(checkPromotion(tempboard, player1Move) && player1Move.promotionType == 0){
                cout << "Need a promotion type." << endl;
                continue;
            }
            
            //make move on real board
            board->movePiece(player1Move.startRow, player1Move.startCol, player1Move.endRow, player1Move.endCol);

            //update piece (if promotion)
            if(checkPromotion(board, player1Move)){
                board->addPiece(player1Move.endRow, player1Move.endCol, player1Move.promotionType, WHITE);
            }

            activePlayer = 2;

            //check checkCheckmate, checkStalemate, checkCheck for player2
            // if(checkCheckmate(BLACK)){
            //     status = CHECKMATEBLACK;
            // }else if(checkCheck(BLACK, board)){
            //     status = BLACKCHECK;
            // }else if(checkStalemate(BLACK)){
            //     status = STALEMATE;
            // }
            // cout << "passing here" << endl;
        }

        if(status == CHECKMATEBLACK){
            cout << "White wins!" << endl;
            p1score +=1;
            break;
        }else if(status == WHITERESIGN){
            cout << "Black wins!" << endl;
            p2score +=1;
            break;
            
        }else if(status == STALEMATE){
            cout << "Stalemate" << endl;
            p1score += 0.5;
            p2score += 0.5;
            break;
        }else if(status == BLACKCHECK){
            cout << "Black is in check!" << endl;
        }
        

        board->render();
        cout << "Black's turn:" << endl;
        cout << "Enter a game command:" << endl;
        //PLAYER2 input loop

        while(activePlayer == 2){
            //call makeMove for player2 (returns a Move class)
            Move player2Move = player2->makeMove(interpreter, board);

            if(player2Move.isResign){
                cout << "Black resigned!" << endl;
                status = BLACKRESIGN;
                break;
            }

            if(player2Move.startCol < 0){ //invalid move
                cout << "Invalid move" << endl;
                continue; //retry
            }

            //check if the move is a valid move
            if(!board->getTile(player2Move.startRow, player2Move.startCol)->getPiece() ||
                board->getTile(player2Move.startRow, player2Move.startCol)->getPiece()->getColour() != BLACK ||
                !board->getTile(player2Move.startRow, player2Move.startCol)->getPiece()
                ->isValidMove(*board, player2Move.startRow, player2Move.startCol, player2Move.endRow, player2Move.endCol)){
            
                //not valid move
                cout << "Invalid piece move. Please try again." << endl;
                continue;
            }

            //make tempboard
            //check if player2 in check, if yes reject
            shared_ptr<Board> tempboard = make_shared<Board>(*board);
            tempboard->movePiece(player2Move.startRow, player2Move.startCol, player2Move.endRow, player2Move.endCol);

            if(checkCheck(BLACK, tempboard)){
                cout << "Black put itself in check. Invalid move." << endl;
                continue;
            }

            //check if we have everything for a promotion if relevant
            if(checkPromotion(tempboard, player2Move) && player2Move.promotionType == 0){
                cout << "Need a promotion type." << endl;
                continue;
            }
            
            //make move on real board
            board->movePiece(player2Move.startRow, player2Move.startCol, player2Move.endRow, player2Move.endCol);

            //update piece (if promotion)
            if(checkPromotion(board, player2Move)){
                board->addPiece(player2Move.endRow, player2Move.endCol, player2Move.promotionType, BLACK);
            }

            activePlayer = 1;

            //check checkCheckmate, checkStalemate, checkCheck for player1
            // if(checkCheckmate(WHITE)){
            //     status = CHECKMATEWHITE;
            // }else if(checkCheck(WHITE, board)){
            //     status = WHITECHECK;
            // }else if(checkStalemate(WHITE)){
            //     status = STALEMATE;
            // }
        }

        if(status == CHECKMATEWHITE){
            cout << "Black wins!" << endl;
            p2score +=1;
            break;
        }else if(status == BLACKRESIGN){
            cout << "White wins!" << endl;
            p1score +=1;
            break;
        }else if(status == STALEMATE){
            cout << "Stalemate" << endl;
            p1score += 0.5;
            p2score += 0.5;
            break;
        }else if(status == WHITECHECK){
            cout << "White is in check!" << endl;
        }


    }
}

void Game::setupLoop() {
    //our loop in set up mode

    while(true){
        //read in commands from interpreter

        //adjust board as needed
    }
}

void Game::runProgram(){

    cout << "Welcome to Chess!" << endl;
    
    Command* command;

    while(true){
        cout << "Start a game or enter set up mode:" << endl;
        //read command
        command = interpreter->readCommand();

        if(!command){
            cout << "Please try again." << endl;
            continue;
        }

        switch(command->getType()){

            case STARTGAME: {
                StartGame* sg_command = static_cast<StartGame*>(command);

                switch(sg_command->getWhitePlayer()){
                    case HUMAN:
                        player1 = new Human{};
                        break;
                    case COMPUTER1:
                        // player1 = new Noob{};
                        break;
                    case COMPUTER2:
                        // player1 = new Intermediate{};
                        break;
                    case COMPUTER3:
                        // player1 = new Pro{};
                        break;
                    case COMPUTER4:
                        // player1 = new Grandmaster{};
                        break;
                }
                
                switch(sg_command->getBlackPlayer()){
                    case HUMAN:
                        player2 = new Human{};
                        break;
                    case COMPUTER1:
                        // player2 = new Noob{};
                        break;
                    case COMPUTER2:
                        // player2 = new Intermediate{};
                        break;
                    case COMPUTER3:
                        // player2 = new Pro{};
                        break;
                    case COMPUTER4:
                        // player2 = new Grandmaster{};
                        break;
                }

                gameLoop();
                break;
            }

            case SETUP: {

                setupLoop();
                break;
            }

            default:{
                cout << "Invalid command in this context. Please try again" << endl;
            }

            
            
        }


    }

}
