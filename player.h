#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"
#include "struct.h"

/*
    玩家类，包括玩家的基本信息
*/

class ChessBoard;

class Player
{
public:
    Player();
    Player(int);
    virtual ~Player();
    virtual Chess doAct(ChessPos, ChessBoard*) = 0;
    virtual bool doWait() = 0;

    void setActive(bool);
    bool getActive();
    void setChesstype(int);
    int getChesstype();
protected:
    bool isactive;
    int chesstype;
};

#endif // PLAYER_H
