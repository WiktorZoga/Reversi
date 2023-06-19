#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

/**************************************************************************************************
 * Menu is a class responsible for the startup screen (maybe in futre also for choosing gamemode)
 * (methods do what they are called)
 **************************************************************************************************/

class Menu {
    WINDOW * menuWindow;

    int menuWindowHeight, menuWindowWidth;

    int menuWindowStarting_y, menuWindowStarting_x;

    void deleteMenu();

public:

    Menu() {}

    void init();

    int run();

};

#endif 