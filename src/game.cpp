#include "game.h"

Game::Game(Ui* _ui, GameMode _gameMode) : ui(_ui), gameMode(_gameMode), activePlayer(BLACK_BLOCK) {

    player1.setPlayerBoard(&board);
    player2.setPlayerBoard(&board);

    player1.setPlayerSide(BLACK_BLOCK);
    player2.setPlayerSide(WHITE_BLOCK);


    switch (gameMode) {
    case HUMAN_VS_HUMAN:
        player1.setPlayerType(HUMAN);
        player2.setPlayerType(HUMAN);
        break;
    case HUMAN_VS_BOT:
        player1.setPlayerType(HUMAN);
        player2.setPlayerType(BOT);
        break;
    case BOT_VS_HUMAN:
        player1.setPlayerType(BOT);
        player2.setPlayerType(HUMAN);
        break;
    }

}

Player* Game::getActivePlayer() {
    if (activePlayer == BLACK_BLOCK) 
        return &player1;
    return &player2;
}

bool Game::gameTick() {
    Player* player = getActivePlayer();
    if (board.doHaveAnyMoves(player->getPlayerSide())) {
        activePlayer = switchType(activePlayer);
    } else {        
        while (true) {
            Move move = player->getMove(ui);
            if (player->makeMove(move)) {
                activePlayer = switchType(activePlayer);
                break;
            }
        }
    }
    return true;
}

bool Game::gameOver() {
    return board.doHaveAnyMoves(WHITE_BLOCK) && board.doHaveAnyMoves(BLACK_BLOCK);
}

BlockType Game::getActivePlayerSide() {
    return getActivePlayer()->getPlayerSide();
}

