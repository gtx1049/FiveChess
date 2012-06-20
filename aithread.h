#ifndef AITHREAD_H
#define AITHREAD_H

#include <QThread>
#include "board.h"
#include "aiplayer.h"

/*
    通过线程控制AI，可使AI思考事件独立，不阻塞GUI线程
*/

class Board;

class AIthread : public QThread
{
    Q_OBJECT
public:
    AIthread();
    AIthread(AIplayer*, ChessBoard*, Board*);
    ~AIthread();
    virtual void run();
    AIplayer* getAIplayer();
private:
    AIplayer* theplayer;
    ChessBoard* maincb;
    Board* theboard;
signals:
    void endThink();
    void judgeLastChess(Chess);
public slots:
    
};

#endif // AITHREAD_H
