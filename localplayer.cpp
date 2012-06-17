#include "localplayer.h"

LocalPlayer::LocalPlayer(int type) :
    Player(type)
{
}

LocalPlayer::~LocalPlayer()
{
}

Chess LocalPlayer::doAct(ChessPos cp, ChessBoard* chessmat)
{
    Chess lastchess = Chess(cp.row, cp.column, this->getChesstype());
    chessmat->setOneChess(lastchess);
    return lastchess;
}

bool LocalPlayer::doWait()
{
    return false;
}

void LocalPlayer::backStep()
{
}
