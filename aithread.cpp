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

}

AIthread::~AIthread()
{
    delete theplayer;
}

void AIthread::run()
{
    theplayer->setActive(true);
    theplayer->doAct(theplayer->thinkStrategy(maincb), maincb);
    emit endThink();
    theplayer->setActive(false);
}

AIplayer *AIthread::getAIplayer()
{
    return theplayer;
}
