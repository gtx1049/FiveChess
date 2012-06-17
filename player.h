#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"
#include "struct.h"

class ChessBoard;

class Player
{
public:
    Player();
    Player(int);
    virtual Chess doAct(ChessPos, ChessBoard*) = 0;
    virtual bool doWait() = 0;

    void setActive(bool);
    bool getActive();
    void setChesstype(int);
    int getChesstype();
private:
    bool isactive;
    int chesstype;
};

#endif // PLAYER_H
