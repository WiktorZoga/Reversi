#include "ui.h"

Ui::Ui(int _mainWindowHeight, int _mainWindowWidth, int _starting_y, int _starting_x) : mainWindowHeight(_mainWindowHeight), mainWindowWidth(_mainWindowWidth), starting_y(_starting_y), starting_x(_starting_x) { initUi(); }

void Ui::initUi() {

    initscr(); 
    cbreak();
    noecho();

    initColors();

    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    { // main mainWindow
        starting_y = (max_y - mainWindowHeight) / 2;

        starting_x = (max_x - mainWindowWidth) / 2;

        mainWindow = newwin(mainWindowHeight, mainWindowWidth, starting_y, starting_x);
        wborder(mainWindow, 's', 's', 's', 's', 'o', 'o', 'o', 'o');
        refresh();
        wrefresh(mainWindow);

        keypad(mainWindow, true);

        curs_set(0);

        last_x = 4, last_y = 4;
    }
    { // status mainWindow
        statusWindowHeight = 4, statusWindowWidth = max_x;
        statusStarting_y = 0, statusStarting_x = 0;
        statusWindow = newwin(statusWindowHeight, statusWindowWidth, statusStarting_y, statusStarting_x);
        refresh();
        wrefresh(statusWindow);
    }

}

void Ui::initColors() {
    start_color();
    init_pair(Clear, COLOR_WHITE, A_NORMAL);  // 0
    init_pair(Black, COLOR_BLACK, A_NORMAL); // 1
    init_pair(Red, COLOR_RED, A_NORMAL);  // 2
    init_pair(Green, COLOR_GREEN, A_NORMAL); // 3
    init_pair(Yellow, COLOR_YELLOW, A_NORMAL); // 4
    init_pair(Blue, COLOR_BLUE, A_NORMAL); // 5
    init_pair(White, COLOR_WHITE, A_NORMAL); // 6

}

void Ui::endUi(Board* board) {
    int countBlack = 0, countWhite = 0;
    for (int row = 0; row < board->getHeight(); row++) {
        for (int col = 0; col < board->getWidth(); col++) {
            BoardPosition position(row, col);
            BlockType type = board->getBlockTypeAt(position);
            if (type == WHITE_BLOCK) {
                countWhite++;
            } else {
                countBlack++;
            }

        }
    }  

    std::string statusX = "X: " + std::to_string(countBlack) + " ";
    std::string statusO = "O: " + std::to_string(countWhite) + "\n" + " ";

    int X = Green, O = Blue;

    if (countBlack == countWhite) {
        X = O = Yellow;
    } else if (countBlack > countWhite) {
        X = Yellow, O = Red;
    } else {
        X = Red, O = Yellow;
    }

    wattron(statusWindow, COLOR_PAIR(X));
    mvwprintw(statusWindow, 1, 1, statusX.c_str());
    wattroff(statusWindow, COLOR_PAIR(X));
    wattron(statusWindow, COLOR_PAIR(O));
    wprintw(statusWindow, statusO.c_str());
    wattroff(statusWindow, COLOR_PAIR(O));
    
    wprintw(statusWindow, "Press any key to close the window.");
    
    wgetch(statusWindow);

    endwin();
}

void Ui::updateUi() {
    wrefresh(mainWindow);
    wrefresh(statusWindow);
}

void Ui::draw(Board* board, BlockType side) {
    updateUi();
    int countBlack = 0, countWhite = 0;
    for (int row = 0; row < board->getHeight(); row++) {
        for (int col = 0; col < board->getWidth(); col++) {
            BoardPosition position(row, col);
            BlockType type = board->getBlockTypeAt(position);
            if (type == EMPTY_BLOCK) {
                if (board->isSetablePosition(position, Block(side))) {
                    wattron(mainWindow, COLOR_PAIR(Yellow));
                    mvwprintw(mainWindow, row + 1, col + 1, "?");
                    wattroff(mainWindow, COLOR_PAIR(Yellow));
                } else  mvwprintw(mainWindow, row + 1, col + 1, ".");
            } else if (type == WHITE_BLOCK) {
                wattron(mainWindow, COLOR_PAIR(Green));
                mvwprintw(mainWindow, row + 1, col + 1, "O");
                wattroff(mainWindow, COLOR_PAIR(Green));
                countWhite++;
            } else {
                wattron(mainWindow, COLOR_PAIR(Blue));
                mvwprintw(mainWindow, row + 1, col + 1, "X");
                wattroff(mainWindow, COLOR_PAIR(Blue));
                countBlack++;
            }
        }
    }
    getStatus(countBlack, countWhite);
}

void Ui::getStatus(int countBlack, int countWhite) {
    std::string statusX = "X: " + std::to_string(countBlack) + " ";
    std::string statusO = "O: " + std::to_string(countWhite);
    wattron(statusWindow, COLOR_PAIR(Green));
    mvwprintw(statusWindow, 1, 1, statusX.c_str());
    wattroff(statusWindow, COLOR_PAIR(Green));
    wattron(statusWindow, COLOR_PAIR(Blue));
    wprintw(statusWindow, statusO.c_str());
    wattroff(statusWindow, COLOR_PAIR(Blue));
}