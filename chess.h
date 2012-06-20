#ifndef CHESS_H
#define CHESS_H

#include <QMetaType>
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
    Chess(const Chess&);
    Chess(int, int, int);
    ~Chess();
    void removeChess();

    int getRow();
    int getColumn();
    int getChessType();
};

//使此类型可以作为信号发射
Q_DECLARE_METATYPE(Chess);

#endif // CHESS_H
