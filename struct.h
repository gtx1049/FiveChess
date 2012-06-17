#ifndef STRUCT_H
#define STRUCT_H

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
