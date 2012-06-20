#ifndef STRUCT_H
#define STRUCT_H

/*
    记录棋子位置的结构体
*/

class ChessPos
{
public:
    int row;
    int column;
    ChessPos(int r, int c):row(r),column(c){}
    ChessPos(){}
    void setPos(int r, int c)
    {
        row = r;
        column = c;
    }
};
#endif // STRUCT_H
