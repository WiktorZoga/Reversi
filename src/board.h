#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include "board_position.h"
#include "move.h"

#include <bits/stdc++.h>

const int BOARD_HEIGHT = 8;
const int BOARD_WIDTH = 8;

const BoardPosition WHITE_STARTING[2] = {BoardPosition(3, 3), BoardPosition(4, 4)};
const BoardPosition BLACK_STARTING[2] = {BoardPosition(3, 4), BoardPosition(4, 3)};

/*************************************************************************************************************
 * Board is a class containing whole board structure and all the methodes needed to operate on the board
 * (methods do what they are called)
 ************************************************************************************************************/

class Board {
    int HEIGHT, WIDTH;

    std::vector<std::vector<Block>> board;

    void resizeBoard(int newHeight, int newWidth);

    void clearPosition(BoardPosition position);

    void setPosition(BoardPosition position, Block block);

    bool isPositionValid(BoardPosition position) const;

    bool isCellFull(BoardPosition position) const;
    bool isCellFree(BoardPosition position) const;

    void setBlock(BoardPosition position, Block block);

    bool isMovePossible(BoardPosition position, MoveDirection direction) const;

public:
    Board(int _HEIGHT = BOARD_HEIGHT, int _WIDTH = BOARD_WIDTH);

    int getHeight() const;
    int getWidth() const;

    void clearBoard();

    const std::vector<std::vector<Block>> getBoard() const;

    BlockType getBlockTypeAt(BoardPosition position) const;
    BlockType getOppBlockTypeAt(BoardPosition position) const;

    bool isSetablePosition(BoardPosition position, Block block);

    bool attemptToSetBlock(BoardPosition position, Block block);
    bool attemptToMakeMove(Move move);

    std::vector<Move> getMoves(BlockType side);

    bool doHaveAnyMoves(BlockType side);

};

#endif