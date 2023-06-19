#include "move.h"

Move::Move(BoardPosition _position, BlockType _type) : position(_position), type(_type) {}

BoardPosition Move::getMovePosition() const { return position; }

BlockType Move::getMoveType() const { return type; }