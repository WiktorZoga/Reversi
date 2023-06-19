#ifndef BLOCK_H
#define BLOCK_H

enum BlockType {
    EMPTY_BLOCK,
    WHITE_BLOCK,
    BLACK_BLOCK
};

/*****************************************************************************************
 * Block is a class contaning current type of block at some position on board
 * (methods do what they are called)
 ****************************************************************************************/
class Block {
    BlockType type;
public:
    Block(BlockType _type = EMPTY_BLOCK);

    BlockType getType() const; 

    BlockType getOppType() const; 
    
    void changeType(BlockType _type); 
};

BlockType switchType(BlockType type); 

#endif