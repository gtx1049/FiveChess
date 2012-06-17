#ifndef CHESS_H
#define CHESS_H

#include "const.h"
/*
    棋子类，记录棋子的位置信息等
*/

class Chess
{
private:
    int chesstype;
    int chessX;
    int chessY;
public:
    Chess();
    Chess(int type, int X, int Y);
    void removeChess();

    int getRow();
    int getColumn();
    int getChessType();
};

#endif // CHESS_H
