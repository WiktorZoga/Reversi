#include "board_position.h"

BoardPosition::BoardPosition(int _row, int _col) : row(_row), col(_col) {}

void BoardPosition::move(MoveDirection direction) {
    row += MOVE_ROW[direction];
    col += MOVE_COL[direction];
}