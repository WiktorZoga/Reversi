#include "board.h"

Board::Board(int _HEIGHT, int _WIDTH) : HEIGHT(_HEIGHT), WIDTH(_WIDTH) {
    resizeBoard(HEIGHT, WIDTH);
    clearBoard();
}

void Board::resizeBoard(int newHeight, int newWidth) {
    board.resize(newHeight);
    for (int row = 0; row < HEIGHT; row++) {
        board[row].assign(newWidth, Block(EMPTY_BLOCK));
    }
}

void Board::clearPosition(BoardPosition position) {
    board[position.row][position.col] = EMPTY_BLOCK;
}

const std::vector<std::vector<Block>> Board::getBoard() const { return board; }

int Board::getHeight() const {
    return HEIGHT;
}
int Board::getWidth() const {
    return WIDTH;
}

bool Board::isPositionValid(BoardPosition position) const {
    if (position.row < 0 || position.row >= (int) HEIGHT)
        return false;
    if (position.col < 0 || position.col >= (int) WIDTH)
        return false;
    return true;
}

void Board::setPosition(BoardPosition position, Block block) {
    board[position.row][position.col] = block.getType();
}

void Board::setBlock(BoardPosition position, Block block) {
    BlockType blockType = block.getType();
    board[position.row][position.col] = blockType;

    if (blockType == EMPTY_BLOCK) 
        return;

    BlockType oppBlockType = block.getOppType();
    
    for (int d = 0; d < 8; d++) {
        MoveDirection direction = (MoveDirection) d;
        if (!isMovePossible(position, direction))
            continue;
        BoardPosition newPosition = position;
        newPosition.move(direction);
        while (getBlockTypeAt(newPosition) == oppBlockType) {
            setPosition(newPosition, block);
            newPosition.move(direction);
        }
    }
}

BlockType Board::getBlockTypeAt(BoardPosition position) const {
    return board[position.row][position.col].getType();
}

BlockType Board::getOppBlockTypeAt(BoardPosition position) const {
    return board[position.row][position.col].getOppType();
}

bool Board::isCellFull(BoardPosition position) const {
    return getBlockTypeAt(position) != EMPTY_BLOCK;
}

bool Board::isCellFree(BoardPosition position) const {
    return getBlockTypeAt(position) == EMPTY_BLOCK;
}

void Board::clearBoard() {
    for (int row = 0; row < HEIGHT; row++) 
        for (int col = 0; col < WIDTH; col++)
            board[row][col] = Block(EMPTY_BLOCK);
    for (int i : {0, 1}) {
        setPosition(WHITE_STARTING[i], Block(WHITE_BLOCK));
        setPosition(BLACK_STARTING[i], Block(BLACK_BLOCK));
    }
}

bool Board::isMovePossible(BoardPosition position, MoveDirection direction) const {
    BlockType type = getBlockTypeAt(position);
    BlockType oppType = getOppBlockTypeAt(position);

    position.move(direction);

    if (!isPositionValid(position) || (getBlockTypeAt(position) != oppType)) 
        return false;
    while (isPositionValid(position) && (getBlockTypeAt(position) == oppType)) {
        position.move(direction);
    }
    return (isPositionValid(position) && getBlockTypeAt(position) == type);
}

bool Board::isSetablePosition(BoardPosition position, Block block) {
    if (getBlockTypeAt(position) != EMPTY_BLOCK) return false;

    setPosition(position, block);
    bool isSetable = false;

    for (int d = 0; d < 8; d++) {
        MoveDirection direction = (MoveDirection) d;
        if (isMovePossible(position, direction)) {
            isSetable = true;
            break;
        }
    }

    clearPosition(position);

    return isSetable;
}

bool Board::attemptToSetBlock(BoardPosition position, Block block) {
    if (!isPositionValid(position) || !isSetablePosition(position, block))
        return false;
    setBlock(position, block);
    return true;
}

bool Board::attemptToMakeMove(Move move) {
    return attemptToSetBlock(move.getMovePosition(), Block(move.getMoveType()));
}

std::vector<Move> Board::getMoves(BlockType side) {
    std::vector<Move> moves;
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            BoardPosition position(row, col);
            if (isCellFull(position)) 
                continue;
            for (int d = 0; d < 8; d++) {
                if (isSetablePosition(position, Block(side))) 
                    moves.push_back(Move(position, side));
            }
        }
    }
    return moves;
}

bool Board::doHaveAnyMoves(BlockType side) {
    return getMoves(side).empty();
}