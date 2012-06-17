#include "chess.h"

Chess::Chess()
{
}

Chess::Chess(int X, int Y, int type)
{
    chesstype = type;
    chessX = X;
    chessY = Y;
}

void Chess::removeChess()
{
    delete this;
}

int Chess::getRow()
{
    return chessX;
}

int Chess::getColumn()
{
    return chessY;
}

int Chess::getChessType()
{
    return chesstype;
}
