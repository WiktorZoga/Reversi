#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include "board.h"

enum TerminalColors {
    Clear, 
    Black, 
    Red, 
    Green, 
    Yellow, 
    Blue, 
    White
};

const int NUMBER_OF_COLORS = 7;

const int OFFSET = 2;

/**************************************************************************************
 * Ui is a class responsible for the entire display of the game onto linux terminal
 * (methods do what they are called)
 **************************************************************************************/

class Ui {

    WINDOW * statusWindow;

    int statusWindowHeight, statusWindowWidth;

    int statusStarting_y, statusStarting_x;

    void getStatus(int countBlack, int countWhite);

    void initColors();

public:

    WINDOW * mainWindow;

    int mainWindowHeight, mainWindowWidth;

    int starting_y, starting_x, last_y, last_x;

    Ui(int _mainWindowHeight = BOARD_HEIGHT + OFFSET, int _mainWindowWidth = BOARD_WIDTH + OFFSET, int start_y = 0, int start_x = 0);

    void initUi();

    void endUi(Board* board);

    void updateUi();

    void draw(Board* board, BlockType side);

};

#endif