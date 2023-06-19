#include "menu.h"
#include <string>

void Menu::init() {

    initscr(); 
    cbreak();
    noecho();

    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    menuWindowHeight = 50, menuWindowWidth = 50;
    menuWindowStarting_y = (max_y - menuWindowHeight) / 2;
    menuWindowStarting_x = (max_x - menuWindowWidth) / 2;

    menuWindow = newwin(menuWindowHeight, menuWindowWidth, menuWindowStarting_y, menuWindowStarting_x);
    box(menuWindow, 0, 0);
    refresh();
    wrefresh(menuWindow);
    keypad(menuWindow, true);

    curs_set(0);
}

int Menu::run() {

    int menuOFFSET = 3;
    int rulesOFFSET = menuOFFSET + 6;


    mvprintw(1, 1, "Hi, would you like to play some Reversi? (press eneter)");
    // mvprintw(1, 1, "Hi, would you like to play some Reversi? (choose one out of three options)");
    // std::string choices[3] = {"1) Play against friend", "2) Play against Bot (You start)", "3) Play against Bot (He starts)" };
    // for (int i = 0; i < 3; i++) {
    //     mvprintw(menuOFFSET + i, 1, choices[i].c_str());
    // }
    mvprintw(menuOFFSET + 0, 1, "You move with the w-s-a-d keys and confirm the movement with enter.");
    std::string rules[6] = {"Standard chess-board rules:", "There are sixty-four identical game pieces called disks, which are light on one side and dark on the other.", "Players take turns placing disks on the board with their assigned color facing up.", "During a play, any disks of the opponent's color that are in a straight line and bounded by", "the disk just placed and another disk of the current player's color are turned over to the current player's color.", "The objective of the game is to have the majority of disks turned to display one's color when the last playable empty square is filled."};
    for (int i = 0; i < 5; i++) {
        mvprintw(rulesOFFSET + i, 1, rules[i].c_str());
    }
    mvprintw(rulesOFFSET - 3, 1, "Good luck!!!");
    wrefresh(menuWindow);

    while (true) {
        char x = getch();
        switch (x) {
            case 10:
                deleteMenu();
                return  0;
            default:
                break;
        }
    }

    // while (true) {
    //     char x = getch();
    //     switch (x) {
    //         case '1':
    //             deleteMenu();
    //             return  0;
    //         case '2':
    //             deleteMenu();
    //             return  1;
    //             break;
    //         case '3':
    //             deleteMenu();
    //             return 2;
    //         default:
    //             break;
    //     }
    // }
    return 0;
}

void Menu::deleteMenu() {
    clear();
    wrefresh(menuWindow);
    delwin(menuWindow);
}