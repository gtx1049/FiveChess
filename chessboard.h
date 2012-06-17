#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<const.h>
#include<vector>
#include"chess.h"
#include"board.h"

using namespace std;


/*
    棋盘类，负责判断胜负，落子等相关事宜
*/

class Board;

class ChessBoard
{
private:
    int chessboardmat[BOARD_SIZE][BOARD_SIZE];
    bool isaviliable;
    std::vector<Chess> steps;
public:
    ChessBoard();
    void reFresh();
    void setOneChess(Chess);
    bool backStep();
    bool judgeVictory(Chess&);
    void waitAct();
    void displayBoard(Board* b);

private:
    bool fiveInDirection(int, int, int, int);
};

#endif // CHESSBOARD_H
