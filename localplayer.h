#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "player.h"

class LocalPlayer : public Player
{
public:
    LocalPlayer(int);
    ~LocalPlayer();
    Chess doAct(ChessPos, ChessBoard*);
    bool doWait();

    void backStep();
};

#endif // LOCALPLAYER_H
