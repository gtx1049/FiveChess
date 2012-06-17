#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIplayer : public Player
{
public:
    AIplayer(int);
    Chess doAct(ChessPos, ChessBoard*);
    bool doWait();
    ChessPos thinkStrategy();
};

#endif // AIPLAYER_H
