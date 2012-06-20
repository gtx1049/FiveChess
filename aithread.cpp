#include "aithread.h"

AIthread::AIthread()
{

}

AIthread::AIthread(AIplayer* p, ChessBoard* cb, Board* b)
{
    theplayer = p;
    theboard = b;
    maincb = cb;

    connect(this, SIGNAL(endThink()), theboard, SLOT(repaintScreen()));
    connect(this, SIGNAL(judgeLastChess(Chess)), theboard, SLOT(judgeVictoryOfAI(Chess)));
}

AIthread::~AIthread()
{
    delete theplayer;
}

void AIthread::run()
{
    theplayer->setActive(true);
    Chess lastchess = theplayer->doAct(theplayer->thinkStrategy(maincb), maincb);
    emit endThink();
    emit judgeLastChess(lastchess);
    theplayer->setActive(false);
}

AIplayer *AIthread::getAIplayer()
{
    return theplayer;
}
