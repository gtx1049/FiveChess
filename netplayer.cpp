#include "netplayer.h"

NetPlayer::NetPlayer(int type) :
    Player(type)
{
}

NetPlayer::~NetPlayer()
{
}

Chess NetPlayer::doAct(ChessPos cp, ChessBoard* chessmat)
{
    Chess lastchess = Chess(cp.row, cp.column, this->getChesstype());
    chessmat->setOneChess(lastchess);
    return lastchess;
}

bool NetPlayer::doWait()
{
    return false;
}
