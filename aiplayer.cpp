#include "aiplayer.h"
#include "struct.h"
#include "aianalyze.h"

AIplayer::AIplayer(int type) :
    Player(type)
{
}

AIplayer::~AIplayer()
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

ChessPos AIplayer::thinkStrategy(ChessBoard* chessmat)
{
    AIanalyze currentstate(chessmat, chesstype, 0);

    return currentstate.analyzeCurrent();

}
