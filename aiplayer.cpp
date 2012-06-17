#include "aiplayer.h"
#include "struct.h"

AIplayer::AIplayer(int type) :
    Player(type)
{
}

Chess AIplayer::doAct(ChessPos cp, ChessBoard* chessmat)
{
    Chess lastchess = Chess(cp.row, cp.column, this->getChesstype());
    chessmat->setOneChess(lastchess);
    return lastchess;
}

bool AIplayer::doWait()
{
    return false;
}

ChessPos AIplayer::thinkStrategy()
{
    return ChessPos(1, 1);
}
