#ifndef GAME_H
#define GAME_H

#include <vector>

#include "player.h"
#include "board.h"
#include "ui.h"

enum GameMode {
    HUMAN_VS_HUMAN,
    HUMAN_VS_BOT, 
    BOT_VS_HUMAN
};

/*************************************************************
 * Game is a class responsible for the course of the game 
 * (methods do what they are called)
 *************************************************************/
class Game {
    GameMode gameMode;
    Player player1, player2;
    BlockType activePlayer;
public:

    Ui* ui;
    Board board;

    Game(Ui* _ui, GameMode _gameMode = HUMAN_VS_HUMAN);

    Player* getActivePlayer();

    BlockType getActivePlayerSide();

    bool gameTick();

    bool gameOver();

};

#endif