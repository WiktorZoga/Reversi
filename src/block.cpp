#include "block.h"

Block::Block(BlockType _type) : type(_type) {}

BlockType Block::getType() const { return type; }

BlockType Block::getOppType() const { return switchType(type); }

void Block::changeType(BlockType _type) { type = _type; }

BlockType switchType(BlockType type) {
    if (type == EMPTY_BLOCK) return EMPTY_BLOCK;
    if (type == WHITE_BLOCK) return BLACK_BLOCK;
    return WHITE_BLOCK;
}