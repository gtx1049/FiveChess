#ifndef NETPLAYER_H
#define NETPLAYER_H

#include "player.h"

class NetPlayer : public Player
{
public:
    NetPlayer(int);
    Chess doAct(ChessPos, ChessBoard*);
    bool doWait();
};

#endif // NETPLAYER_H
