#ifndef AIPLAYER_H
#define AIPLAYER_H

#include"player.h"

/*
    AI玩家类，继承自玩家类
*/

class Player;
class ChessPos;
class ChessBoard;

class AIplayer : public Player
{
public:
    AIplayer(int);
    ~AIplayer();
    Chess doAct(ChessPos, ChessBoard*);
    bool doWait();
    ChessPos thinkStrategy(ChessBoard*);
};

#endif // AIPLAYER_H
