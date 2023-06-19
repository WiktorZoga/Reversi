#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "ui.h"
// #include "ai.h"

enum PlayerType {
    HUMAN,
    BOT
};

/*******************************************************************************************************************
 * Player is a class containing whole player structure and all the methodes player needs in playing out a move
 * (methods do what they are called)
 ******************************************************************************************************************/

class Player {
    PlayerType playerType;
    BlockType playerSide;
    Board* board;

public:
    Player(PlayerType _playerType = HUMAN, BlockType _playerSide = WHITE_BLOCK);

    Move getMove(Ui* ui);

    bool makeMove(Move move);

    PlayerType getPlayerType() const;
    BlockType getPlayerSide() const;

    void setPlayerType(PlayerType _playerType);
    void setPlayerSide(BlockType _playerSide);
    void setPlayerBoard(Board* _board);

    Board getBoard() const;

};

#endif