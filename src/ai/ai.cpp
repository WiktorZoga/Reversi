#ifndef AI_H
#define AI

#include "board.h"

class Ai {

    const int MAX_DEPTH = 3;
    const int INF = 1e9;

    BlockType side;

    BlockType getSide() const;

    void setSide(BlockType _side);

    Move alphaBetaRoot();

    int alphaBeta();

    int utility() const;

    int heuristicValue() const;

    int calcRatio() const;

public:

    Move getBestMove();

};

#endif AI_H