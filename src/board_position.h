#ifndef BOARD_POSITION_H
#define BOARD_POSITION_H

#include <array>

enum MoveDirection {
    UP, 
    UP_RIGHT,
    RIGHT, 
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT, 
    UP_LEFT
};

const std::array<int, 8> MOVE_ROW = {-1, -1, 0, +1, +1, +1, 0, -1};
const std::array<int, 8> MOVE_COL = {0, +1, +1, +1, 0, -1, -1, -1};

/*************************************************************
 * BoardPosition is some position on board (row and column)
 * (methods do what they are called)
 *************************************************************/

class BoardPosition {
public:
    int row, col;
    BoardPosition(int _row = -1, int _col = -1);

    void move(MoveDirection dierction);
};

#endif