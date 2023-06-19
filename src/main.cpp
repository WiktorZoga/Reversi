#include <bits/stdc++.h>

#include "game.h"
#include "ui.h"
#include "menu.h"

int main(int argc, char *argv[]) {

    Menu menu;

    menu.init();

    int gameMode = menu.run();

    Ui ui;

    Game game(&ui, (GameMode) gameMode);

    ui.draw(&game.board, game.getActivePlayerSide());
    ui.updateUi();

    /*************
     * Game loop
     *************/

    while(!game.gameOver()) {
        ui.draw(&game.board, game.getActivePlayerSide());
        if (game.gameTick()) {}
        ui.updateUi();
    }

    ui.endUi(&game.board);

    return 0;
}