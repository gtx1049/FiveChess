#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

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
