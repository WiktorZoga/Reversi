#ifndef MOVE_H
#define MOVE_H

#include "board_position.h"
#include "block.h"

/*************************************************************************************************************
 * Move is a class containing position and type of block which is to be placed on board
 * (methods do what they are called)
 ************************************************************************************************************/

class Move {
    BoardPosition position;
    BlockType type;
public:
    Move(BoardPosition _position = BoardPosition(), BlockType _type = EMPTY_BLOCK);

    BoardPosition getMovePosition() const;
    BlockType getMoveType() const;
};

#endif
