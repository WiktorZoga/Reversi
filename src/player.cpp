#include "player.h"

Player::Player(PlayerType _playerType, BlockType _playerSide) : playerType(_playerType), playerSide(_playerSide) {}

PlayerType Player::getPlayerType() const { return playerType; }
BlockType Player::getPlayerSide() const { return playerSide; }

void Player::setPlayerType(PlayerType _playerType) { playerType = _playerType; }

void Player::setPlayerSide(BlockType _playerSide) { playerSide = _playerSide; }

void Player::setPlayerBoard(Board* _board) { board = _board; }

Move Player::getMove(Ui* ui) {
    int y = ui->last_y, x = ui->last_x;
    wmove(ui->mainWindow, y, x);
    if (playerType == HUMAN) {
        while (true) {

            ui->draw(board, getPlayerSide());

            wattron(ui->mainWindow, COLOR_PAIR(2));

            mvwprintw(ui->mainWindow, y, x, "@");

            wattroff(ui->mainWindow, COLOR_PAIR(2));

            wmove(ui->mainWindow, y, x);

            char c = wgetch(ui->mainWindow);

            if (c == 'w')
                y = std::max(1, y - 1);
            else if (c == 's') 
                y = std::min(board->getHeight(), y + 1);
            else if (c == 'a')
                x = std::max(1, x - 1);
            else if (c == 'd')
                x = std::min(board->getWidth(), x + 1);
            else if (c == 10) { // enter
                ui->last_x = x, ui->last_y = y;
                return Move(BoardPosition(y - 1, x - 1), getPlayerSide()); // pamiętaj o tym offsecie 
            }
            
        }
    }
    return Move(BoardPosition(-1, -1), getPlayerSide());
}

bool Player::makeMove(Move move) {
    return (this)->board->attemptToMakeMove(move);
}

Board Player::getBoard() const {
    return *board;
}


