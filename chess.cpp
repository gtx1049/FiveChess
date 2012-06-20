#include "chess.h"

Chess::Chess()
{
}

Chess::Chess(const Chess &c)
{
    chesstype = c.chesstype;
    chessX = c.chessX;
    chessY = c.chessY;
}

Chess::Chess(int X, int Y, int type)
{
    chesstype = type;
    chessX = X;
    chessY = Y;
}

Chess::~Chess()
{
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
